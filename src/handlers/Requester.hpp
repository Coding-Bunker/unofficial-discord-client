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
    void guildsFinished(const QJsonArray &array);
    void channelsListForGuild(snowflake guildID, QStringList channels);

  private slots:
    void handleGuilds(QVariant dummy);
    void handleChannels(QVariant id);

  private:
    QString m_token;
    QNetworkAccessManager m_nam;

    template<typename T> void request(const QString &api, T callback);
};
