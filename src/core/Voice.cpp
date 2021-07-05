//#include <QAudioInput>
//#include <QtMultimedia>

#include "Voice.hpp"

// const auto &input_device{ QAudioDeviceInfo::defaultInputDevice() },
//  &output_device{ QAudioDeviceInfo::defaultOutputDevice() };

snowflake Voice::user_id() const
{
    return m_user_id;
}

snowflake Voice::channel_id() const
{
    return m_channel_id;
}

const QByteArray &Voice::session_id() const
{
    return m_session_id;
}

bool Voice::deaf() const
{
    return m_deaf;
}

bool Voice::mute() const
{
    return m_mute;
}

bool Voice::self_deaf() const
{
    return m_self_deaf;
}

bool Voice::self_mute() const
{
    return m_self_mute;
}

bool Voice::camera_on() const
{
    return m_camera_on;
}

bool Voice::surpress() const
{
    return m_surpress;
}

const QDateTime &Voice::requested_to_speak() const
{
    return m_requested_to_speak;
}

optional<snowflake> Voice::guild_id() const
{
    return m_guild_id;
}

optional<bool> Voice::self_stream() const
{
    return m_self_stream;
}

optional<GuildMember> &Voice::member()
{
    return m_member;
}

void Voice::unmarshal(const QJsonObject &&o)
{
    if (o.contains(QStringLiteral("guild_id")))
        m_guild_id = o[QStringLiteral("guild_id")].toString().toULongLong();
    if (!o[QStringLiteral("channel_id")].isNull())
        m_channel_id = o[QStringLiteral("channel_id")].toString().toULongLong();
    m_user_id = o[QStringLiteral("user_id")].toString().toULongLong();
    if (o.contains(QStringLiteral("member"))) {
        GuildMember g;
        g.unmarshal(o[QStringLiteral("member")].toObject());
        m_member.emplace(g);
    }
    m_session_id = o[QStringLiteral("session_id")].toString().toLocal8Bit();
    m_deaf       = o[QStringLiteral("deaf")].toBool();
    m_mute       = o[QStringLiteral("mute")].toBool();
    m_self_deaf  = o[QStringLiteral("self_deaf")].toBool();
    m_self_mute  = o[QStringLiteral("self_mute")].toBool();
    m_camera_on  = o[QStringLiteral("self_video")].toBool();
    m_surpress   = o[QStringLiteral("surpress")].toBool();
    if (!o[QStringLiteral("request_to_speak_tinestamp")].isNull())
        m_requested_to_speak = QDateTime::fromString(
            o[QStringLiteral("request_to_speak_timestamo")].toString());
}

void Voice_Region::unmarshal(const QJsonObject &&o)
{
    m_id         = o[QStringLiteral("id")].toString().toLocal8Bit();
    m_name       = o[QStringLiteral("name")].toString();
    m_vip        = o[QStringLiteral("vip")].toBool();
    m_optimal    = o[QStringLiteral("optimal")].toBool();
    m_deprecated = o[QStringLiteral("deprecated")].toBool();
    m_custom     = o[QStringLiteral("custom")].toBool();
}

const QByteArray &Voice_Region::id() const
{
    return m_id;
}

const QString &Voice_Region::name() const
{
    return m_name;
}

bool Voice_Region::vip() const
{
    return m_vip;
}

bool Voice_Region::optimal() const
{
    return m_optimal;
}

bool Voice_Region::deprecated() const
{
    return m_deprecated;
}

bool Voice_Region::custom() const
{
    return m_custom;
}
