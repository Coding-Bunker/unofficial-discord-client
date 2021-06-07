#pragma once

#include "core/Types.hpp"

#include <QNetworkAccessManager>

class Requester : public QObject
{
    Q_OBJECT

  public:
    void setToken(const QString &token);

  public:
    void initWebsocket();

    void requestGuilds();
    void requestChannels(const QList<snowflake> &guildIDs);
    void requestGuildsImages(QList<QPair<snowflake, QString>> &&items);

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
    QString m_websocketAddress;

    QNetworkReply *request(const QString &api);
};
