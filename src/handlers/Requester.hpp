#pragma once

#include "core/Types.hpp"

#include <QNetworkAccessManager>
#include <utility>

class Requester : public QObject
{
    Q_OBJECT

  public:
    explicit Requester(QObject *parent = nullptr);

    void setToken(const QString &token);

  public:
    void requestGuilds();
    void requestChannels(const QList<snowflake> &guildIDs);
    void
    requestGuildsImages(const QList<std::pair<snowflake, QString>> &&items);

  public slots:
    void requestMessages(snowflake channelID);
    void sendMessage(snowflake channelID, QString txt);

  signals:
    void guildsFinished(QByteArray data);
    void channelFinished(QByteArray data);
    void messagesFinished(QByteArray data);
    void guildIconBase64(snowflake guildID, QByteArray imgBase64);

  private:
    QString m_token;
    QNetworkAccessManager m_nam;

    QNetworkReply const *request(const QString &api);
};
