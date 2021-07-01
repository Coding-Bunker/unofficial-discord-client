#pragma once

#include "DiscordApi/DiscordAPI.hpp"
#include "User.hpp"

#include <QJsonObject>
#include <memory>
#include <optional>

using std::optional;

class GuildMember
{
    // std::unique_ptr<User> m_user;
    optional<bool> m_pending;
    optional<QString> m_nick, m_permissions;
    optional<QDateTime> m_premium_join_time;
    QList<snowflake> m_roles;
    QDateTime m_join_time;
    bool m_deaf, m_mute;

  public:
    void unmarshal(const QJsonObject &o)
    {
        unmarshal(std::move(o));
    }
    void unmarshal(const QJsonObject &&);
    optional<bool> pending() const;
    optional<QString> nick() const;
    optional<QString> permissions() const;
    optional<QDateTime> premium_join_time() const;
    const QList<snowflake> &roles() const;
    const QDateTime &join_time() const;
    bool deaf() const;
    bool mute() const;
};
