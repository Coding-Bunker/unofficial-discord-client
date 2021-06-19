#pragma once

#include "Guild.hpp"
#include "Types.hpp"

#include <QDateTime>
#include <QJsonObject>
#include <optional>
#include <utility>

using std::optional;
class Voice
{
    snowflake m_user_id, m_channel_id;
    optional<snowflake> m_guild_id;
    optional<bool> m_self_stream;
    optional<Guild_Member> m_member;
    QByteArray m_session_id;
    bool m_deaf, m_mute, m_self_deaf, m_self_mute, m_camera_on, m_surpress;
    QDateTime m_requested_to_speak;

  public:
    void unmarshal(const QJsonObject &o)
    {
        unmarshal(std::move(o));
    }
    void unmarshal(const QJsonObject &&);
    snowflake user_id() const;
    snowflake channel_id() const;
    const QByteArray &session_id() const;
    bool deaf() const;
    bool mute() const;
    bool self_deaf() const;
    bool self_mute() const;
    bool camera_on() const;
    bool surpress() const;
    const QDateTime &requested_to_speak() const;
    optional<snowflake> guild_id() const;
    optional<bool> self_stream() const;
    optional<Guild_Member> member() const;
};

class Voice_Region
{
    QByteArray m_id;
    QString m_name;
    bool m_vip, m_optimal, m_deprecated, m_custom;

  public:
    void unmarshal(const QJsonObject &o)
    {
        unmarshal(std::move(o));
    }
    void unmarshal(const QJsonObject &&);
    const QByteArray &id() const;
    const QString &name() const;
    bool vip() const;
    bool optimal() const;
    bool deprecated() const;
    bool custom() const;
};
