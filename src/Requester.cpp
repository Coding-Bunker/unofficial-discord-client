#include "Requester.hpp"

#include "DiscordApi/DiscordAPI.hpp"

#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

Requester::Requester(QObject *parent) : QObject(parent) {}

void Requester::setToken(const QString &token)
{
    m_token = token;
}

void Requester::requestGuilds()
{
    request(DiscordAPI::guilds);
}

void Requester::response()
{
    const auto r = qobject_cast<QNetworkReply *>(sender());
    if (r == nullptr) {
        qWarning() << Q_FUNC_INFO << "error response";
        return;
    }

    r->deleteLater();
    qDebug() << r->readAll();
}

void Requester::request(const QString &api)
{
    QUrl url(api);
    QNetworkRequest req(url);
    QString headerData = "Bearer " + m_token;
    req.setRawHeader("Authorization", headerData.toLocal8Bit());
    req.setHeader(QNetworkRequest::ContentTypeHeader,
                  "application/x-www-form-urlencoded");
    auto reply = m_nam.get(req);
    connect(reply, &QNetworkReply::finished, this, &Requester::response);
}
