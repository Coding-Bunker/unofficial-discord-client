#pragma once

#include "core/Types.hpp"

#include <QNetworkAccessManager>

class Requester : public QObject
{
    Q_OBJECT

  public:
    explicit Requester(QObject *parent = nullptr);

    void setToken(const QString &token);

  public:
    void requestGuilds();
    void requestChannels(const QList<snowflake> &guildIDs);
    void requestGuildsImages(QList<QPair<snowflake, QString>> &&items);

  public slots:
    void requestMessages(snowflake channelID);

  signals:
    void guildsFinished(QByteArray data);
    void channelFinished(QByteArray data);
    void messagesFinished(QByteArray data);
    void guildIconBase64(snowflake guildID, QByteArray imgBase64);

  private:
    QString m_token;
    QNetworkAccessManager m_nam;

    QNetworkReply *request(const QString &api);
};
