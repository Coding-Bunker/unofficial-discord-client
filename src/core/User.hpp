#pragma once

#include "Guild.hpp"
#include "Types.hpp"

#include <QVector>
#include <QtDebug>

class QJsonArray;

class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool logged READ logged NOTIFY loggedChanged)
    Q_PROPERTY(QString username READ username NOTIFY loggedChanged)

  public:
    void populate(const QJsonDocument &doc);

    bool logged() const;

    QString username() const;

    void setGuilds(const QByteArray &data);
    const QVector<Guild> &guilds() const noexcept;
    QVector<snowflake> guildIDs() const noexcept;

    void setChannelsForGuild(const QByteArray &data);

    friend QDebug operator<<(QDebug dbg, const User &u);

  signals:
    void loggedChanged();

  private:
    bool m_logged{ false };
    snowflake m_id;
    QString m_username;
    QString m_avatar;
    QString m_discriminator;
    QVector<Guild> m_guilds;
};
