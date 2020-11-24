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
    void requestChannels(const QVector<snowflake> &guildIDs);

  signals:
    void guildsFinished(QByteArray data);
    void channelFinished(QByteArray data);

  private:
    QString m_token;
    QNetworkAccessManager m_nam;

    QNetworkReply *request(const QString &api);
};
