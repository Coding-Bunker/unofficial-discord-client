#include "Authenticator.hpp"

#include "DiscordApi/DiscordAPI.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QSettings>

void Authenticator::requestLogin(QString email, QString pass, QString twoFA)
{
    QNetworkRequest req(DiscordAPI::login);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("User-Agent", DiscordAPI::fakeBrowserUserAgent);

    QJsonObject data;
    data["email"]    = email;
    data["password"] = pass;
    QJsonDocument doc(data);

    const auto reply = m_nam.post(req, doc.toJson());
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r = qobject_cast<QNetworkReply *>(sender());
        r->deleteLater();

        // TODO: check error before proceding

        handleLoginResponse(r->readAll(), twoFA);
    });
}

void Authenticator::handleLoginResponse(QString body, QString twoFA)
{
    const auto doc = QJsonDocument::fromJson(body.toLatin1());
    const auto obj = doc.object();

    const auto token  = obj.value("token").toString();
    const auto mfa    = obj.value("mfa").toBool();
    const auto sms    = obj.value("sms").toBool();
    const auto ticket = obj.value("ticket").toString();

    Q_UNUSED(sms) // TODO: handle sms

    if (mfa) {
        request2FA(ticket, twoFA);
        return;
    }

    m_token = token;
    handlePersonInfo();
}

void Authenticator::request2FA(QString ticket, QString mfa)
{
    QNetworkRequest req(DiscordAPI::mfa);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("User-Agent", DiscordAPI::fakeBrowserUserAgent);

    QJsonObject data;
    data["code"]             = mfa;
    data["gift_code_sku_id"] = "";
    data["login_source"]     = "";
    data["ticket"]           = ticket;
    QJsonDocument doc(data);

    const auto reply = m_nam.post(req, doc.toJson());
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r = qobject_cast<QNetworkReply *>(sender());
        r->deleteLater();
        const auto doc = QJsonDocument::fromJson(r->readAll());
        const auto obj = doc.object();
        m_token        = obj.value("token").toString();
        handlePersonInfo();
    });
}

void Authenticator::handlePersonInfo()
{
    QNetworkRequest req(DiscordAPI::me);
    req.setRawHeader("authorization", m_token.toLatin1());
    req.setRawHeader("User-Agent", DiscordAPI::fakeBrowserUserAgent);

    const auto reply = m_nam.get(req);
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r = qobject_cast<QNetworkReply *>(sender());
        r->deleteLater();
        const auto info = QJsonDocument::fromJson(r->readAll());
        saveSettings(info);
        emit authenticationSuccess(m_token, info);
    });
}

void Authenticator::saveSettings(const QJsonDocument &info)
{
    QSettings settings(QSettings::Format::NativeFormat,
                       QSettings::Scope::UserScope,
                       "unofficial-discord-client");
    settings.setValue("auth/token", m_token);
    settings.setValue("auth/meInfo", info.toJson());
    settings.sync();
}
