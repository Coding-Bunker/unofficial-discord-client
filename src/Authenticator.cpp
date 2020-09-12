#include "Authenticator.hpp"

#include "DiscordApi/DiscordAPI.hpp"

#include <QDesktopServices>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTcpSocket>
#include <QUrlQuery>

Authenticator::Authenticator(QObject *parent) : QObject(parent)
{
    connect(&m_localServer, &QTcpServer::newConnection, this,
            &Authenticator::newConnectionOnLocalServer);
    m_localServer.listen(QHostAddress::LocalHost, 8000);
}

Authenticator::~Authenticator()
{
    if (m_localServer.isListening()) {
        m_localServer.close();
    }
}

void Authenticator::requestLogin()
{
    QUrl url(DiscordAPI::authorize);
    QUrlQuery query;
    query.addQueryItem("response_type", "code");
    query.addQueryItem("client_id", DiscordAPI::clientId);
    query.addQueryItem("scope", "identify%20email%20guilds");
    query.addQueryItem("redirect_uri", "http://localhost:8000");
    url.setQuery(query);
    QDesktopServices::openUrl(url);
}

void Authenticator::newConnectionOnLocalServer()
{
    const auto s   = qobject_cast<QTcpServer *>(sender());
    const auto sok = s->nextPendingConnection();
    if (sok == nullptr) {
        qWarning() << Q_FUNC_INFO << "sok is nullptr";
        return;
    }

    connect(sok, &QTcpSocket::readyRead, this,
            &Authenticator::readDataFromSocket);
    connect(sok, &QTcpSocket::disconnected, sok, &QTcpSocket::deleteLater);
}

void Authenticator::readDataFromSocket()
{
    const auto s = qobject_cast<QTcpSocket *>(sender());
    if (s == nullptr) {
        qWarning() << Q_FUNC_INFO << "bad sender";
        return;
    }

    const auto data = s->readAll();
    const auto v    = data.split('=');
    m_codeGrant     = v.at(1).left(30);
    requestToken();
}

void Authenticator::tokenResponse()
{
    const auto r = qobject_cast<QNetworkReply *>(sender());
    if (r == nullptr) {
        qWarning() << Q_FUNC_INFO << "error response";
        return;
    }

    r->deleteLater();
    const auto doc = QJsonDocument::fromJson(r->readAll());
    const auto obj = doc.object();
    m_token = obj.value(DiscordAPI::DiscordTags::access_token).toString();
    m_refreshToken =
        obj.value(DiscordAPI::DiscordTags::refresh_token).toString();
    m_expireSeconds = obj.value(DiscordAPI::DiscordTags::expires_in).toInt();
    // TODO(guerra): make POST before this time elaps for refreshing token

    requestMeInfo();
}

void Authenticator::infoResponse()
{
    const auto r = qobject_cast<QNetworkReply *>(sender());
    if (r == nullptr) {
        qWarning() << Q_FUNC_INFO << "error response";
        return;
    }

    r->deleteLater();
    qDebug() << r->readAll();
    m_localServer.close();
    emit authenticationFinished(m_token);
}

void Authenticator::requestToken()
{
    QUrl url(DiscordAPI::token);
    QUrlQuery query;
    query.addQueryItem("client_id", DiscordAPI::clientId);
    query.addQueryItem("client_secret", DiscordAPI::clientSecret);
    query.addQueryItem("grant_type", "authorization_code");
    query.addQueryItem("code", m_codeGrant);
    query.addQueryItem("redirect_uri", "http://localhost:8000");
    query.addQueryItem("scope", "identify email connections");
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  "application/x-www-form-urlencoded");
    auto reply = m_nam.post(req, query.query().toUtf8());
    connect(reply, &QNetworkReply::finished, this,
            &Authenticator::tokenResponse);
}

void Authenticator::requestMeInfo()
{
    QUrl url(DiscordAPI::me);
    QNetworkRequest req(url);
    QString headerData = "Bearer " + m_token;
    req.setRawHeader("Authorization", headerData.toLocal8Bit());
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  "application/x-www-form-urlencoded");
    auto reply = m_nam.get(req);
    connect(reply, &QNetworkReply::finished, this,
            &Authenticator::infoResponse);
}
