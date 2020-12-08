#pragma once

#include "Guild.hpp"
#include "Types.hpp"

#include <QVector>
#include <QtDebug>

class QJsonArray;

class User : public QObject
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged)
    // clang-format on

  public:
    void populate(const QJsonDocument &doc);

    QString username() const;

    void setGuilds(const QByteArray &data);
    const QList<Guild> &guilds() const noexcept;
    QList<snowflake> guildIDs() const noexcept;

    void setChannelsForGuild(const QByteArray &data);

    friend QDebug operator<<(QDebug dbg, const User &u);

  signals:
    void usernameChanged();

  private:
    snowflake m_id;
    QString m_username;
    QString m_avatar;
    QString m_discriminator;
    QList<Guild> m_guilds;
};
