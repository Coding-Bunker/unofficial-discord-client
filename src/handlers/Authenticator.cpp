#include "Authenticator.hpp"

#include "DiscordApi/DiscordAPI.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QSettings>

void Authenticator::requestLogin(QString &email, QString &pass, QString &twoFA)
{
    QNetworkRequest req(DiscordAPI::login);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    req.setRawHeader("User-Agent", DiscordAPI::fakeBrowserUserAgent);

    QJsonObject data;
    data["email"]    = email;
    data["password"] = pass;
    QJsonDocument doc(data);

    const auto *reply{ m_nam.post(req, doc.toJson()) };
    connect(reply, &QNetworkReply::finished, this, [this, twoFA]() {
        const auto r{ qobject_cast<QNetworkReply *>(sender()) };
        r->deleteLater();

        if (r->error() != QNetworkReply::NetworkError::NoError) {
            handleLoginFailure(r->error(), r->readAll());
        } else {
            handleLoginResponse(r->readAll(), twoFA);
        }
    });
}

void Authenticator::handleLoginFailure(QNetworkReply::NetworkError error,
                                       QString body)
{
    QString messageError = "";

    if (301 <= error && error <= 399) {
        const auto &doc{ QJsonDocument::fromJson(body.toLatin1()) };
        const auto &obj{ doc.object() };

        if (obj.value("email").isArray() || obj.value("password").isArray()) {
            if (obj.value("email").isArray()) {
                const QJsonArray &emailResponses{
                    obj.value("email").toArray()
                };
                messageError += "On email: ";
                for (const auto &error : emailResponses) {
                    messageError += error.toString() + "\n";
                }
            }
            if (obj.value("password").isArray()) {
                const QJsonArray &passwordResponses{
                    obj.value("password").toArray()
                };
                messageError += "On password: ";
                for (const auto &error : passwordResponses) {
                    messageError += error.toString() + "\n";
                }
            }
        }
    } else {
        messageError += "Network error";
    }

    emit authenticationFailed(QString::number(error), messageError);
}

void Authenticator::handleLoginResponse(QString body, QString twoFA)
{
    const auto &doc{ QJsonDocument::fromJson(body.toLatin1()) };
    const auto &obj{ doc.object() };

    const auto &token{ obj.value("token").toString() };
    const auto mfa{ obj.value("mfa").toBool() };
    const auto sms{ obj.value("sms").toBool() };
    const auto &ticket{ obj.value("ticket").toString() };

    Q_UNUSED(sms) // TODO: handle sms

    if (mfa) {
        if (twoFA.isEmpty() || twoFA.isNull()) {
            emit authenticationFailed("", "2FA required.");
            return;
        }
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

    const auto *reply{ m_nam.post(req, doc.toJson()) };
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r{ qobject_cast<QNetworkReply *>(sender()) };
        r->deleteLater();
        const auto &doc{ QJsonDocument::fromJson(r->readAll()) };
        const auto &obj{ doc.object() };
        m_token = obj.value("token").toString();
        handlePersonInfo();
    });
}

void Authenticator::handlePersonInfo()
{
    QNetworkRequest req(DiscordAPI::me);
    req.setRawHeader("authorization", m_token.toLatin1());
    req.setRawHeader("User-Agent", DiscordAPI::fakeBrowserUserAgent);

    const auto *reply{ m_nam.get(req) };
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r{ qobject_cast<QNetworkReply *>(sender()) };
        r->deleteLater();
        const auto &info{ QJsonDocument::fromJson(r->readAll()) };
        emit saveSettings(m_token, info.toJson());
        emit authenticationSuccess(m_token, info);
    });
}
