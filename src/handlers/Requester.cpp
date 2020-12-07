#include "Requester.hpp"

#include "DiscordApi/DiscordAPI.hpp"

#include <QJsonDocument>
#include <QNetworkReply>

Requester::Requester(QObject *parent) : QObject(parent) {}

void Requester::setToken(const QString &token)
{
    m_token = token;
}

void Requester::requestGuilds()
{
    auto reply = request(DiscordAPI::guilds);
    connect(reply, &QNetworkReply::finished, this, [&]() {
        const auto r = qobject_cast<QNetworkReply *>(sender());
        r->deleteLater();
        emit guildsFinished(r->readAll());
    });
}

void Requester::requestChannels(const QList<snowflake> &guildIDs)
{
    for (auto id : guildIDs) {
        const auto reply = request(DiscordAPI::channels.arg(id));
        connect(reply, &QNetworkReply::finished, this, [&]() {
            const auto r = qobject_cast<QNetworkReply *>(sender());
            r->deleteLater();
            emit channelFinished(r->readAll());
        });
    }
}

QNetworkReply *Requester::request(const QString &api)
{
    QUrl url(api);
    QNetworkRequest req(url);
    req.setRawHeader("authorization", m_token.toLatin1());
    return m_nam.get(req);
}
