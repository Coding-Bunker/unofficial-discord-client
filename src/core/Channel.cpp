#include "Channel.hpp"

void Channel::unmarshal(const QJsonObject &obj)
{
    // clazy:excludeall=qt4-qstring-from-array
    m_id       = obj[QStringLiteral("id")].toString().toULongLong();
    m_name     = obj[QStringLiteral("name")].toString();
    m_nfsw     = obj[QStringLiteral("nfwm")].toBool();
    m_parentId = obj[QStringLiteral("parent_id")].toString().toULongLong();
    m_guildId  = obj[QStringLiteral("guild_id")].toString().toULongLong();
    m_position = obj[QStringLiteral("position")].toInt();
    m_topic    = obj[QStringLiteral("topic")].toString();
    m_last_message_id =
        obj[QStringLiteral("last_message_id")].toString().toULongLong();
    rate_limit_per_user =
        obj[QStringLiteral("rate_limit_per_user")].toString().toUShort();
    m_type        = static_cast<Type>(obj[QStringLiteral("type")].toInt());
    message_count = obj[QStringLiteral("message_count")].toString().toUShort();
    member_count  = obj[QStringLiteral("member_count")].toString().toUShort();
}

snowflake Channel::id() const
{
    return m_id;
}

QString Channel::name() const
{
    return m_name;
}

snowflake Channel::guildId() const
{
    return m_guildId;
}

int Channel::position() const
{
    return m_position;
}

Channel::Type Channel::type() const
{
    return m_type;
}
