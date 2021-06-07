#include "Requester.hpp"

#include "DiscordApi/DiscordAPI.hpp"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

void Requester::setToken(const QString &token)
{
    m_token = token;
}

void Requester::initWebsocket()
{
    const auto *reply{ request(DiscordAPI::gateway) };
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r{ qobject_cast<QNetworkReply *>(sender()) };
        r->deleteLater();
        const auto doc     = QJsonDocument::fromJson(r->readAll());
        const auto obj     = doc.object();
        m_websocketAddress = obj.value("url").toString();
    });
}

void Requester::requestGuilds()
{
    const auto *reply{ request(DiscordAPI::guilds) };
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r{ qobject_cast<QNetworkReply *>(sender()) };
        r->deleteLater();
        emit guildsFinished(r->readAll());
    });
}

void Requester::requestChannels(const QList<snowflake> &guildIDs)
{
    for (auto id : guildIDs) {
        const auto *reply{ request(DiscordAPI::channels.arg(id)) };
        connect(reply, &QNetworkReply::finished, this, [&]() {
            const auto r{ qobject_cast<QNetworkReply *>(sender()) };
            r->deleteLater();
            emit channelFinished(r->readAll());
        });
    }
}

void Requester::requestGuildsImages(
    const QList<std::pair<snowflake, QString>> &&items)
{
    for (const auto &i : items) {
        if (i.second.isEmpty()) {
            continue;
        }

        const auto *reply{ request(
            DiscordAPI::guildIcon.arg(i.first).arg(i.second)) };
        connect(reply, &QNetworkReply::finished, this, [this, i]() {
            const auto r{ qobject_cast<QNetworkReply *>(sender()) };
            r->deleteLater();
            emit guildIconBase64(i.first, r->readAll());
        });
    }
}

void Requester::requestMessages(snowflake channelID)
{
    const auto *reply{ request(DiscordAPI::messages.arg(channelID)) };
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r{ qobject_cast<QNetworkReply *>(sender()) };
        r->deleteLater();
        emit messagesFinished(r->readAll());
    });
}

void Requester::sendMessage(snowflake channelID, QString txt)
{
    QUrl url(DiscordAPI::messages.arg(channelID));
    QNetworkRequest msg(url);
    msg.setRawHeader("authorization", m_token.toLatin1());
    msg.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["content"] = txt;
    QJsonDocument doc(data);

    const auto post{ m_nam.post(msg, doc.toJson()) };
    connect(post, &QNetworkReply::finished, this, [=]() {
        if (post->error() != QNetworkReply::NoError) {
            qDebug() << post->errorString();
        }
        post->deleteLater();
    });
}

QNetworkReply const *Requester::request(const QString &api)
{
    QUrl url{ api };
    QNetworkRequest req{ url };
    req.setRawHeader("authorization", m_token.toLatin1());
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    return m_nam.get(req);
}
