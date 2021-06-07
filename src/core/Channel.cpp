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

/*
bool key_exists(const QJsonObject &k, QString &l)
{
    return !k.value(l).isNull();
}*/

snowflake Channel::id() const
{
    return m_id;
}

optional<QString> Channel::name() const
{
    return m_name;
}

optional<snowflake> Channel::guildId() const
{
    return m_guildId;
}

optional<int> Channel::position() const
{
    return m_position;
}

Channel::Type Channel::type() const
{
    return m_type;
}

optional<snowflake> Channel::last_message_id() const
{
    return m_last_message_id;
}

snowflake Channel::parentId() const
{
    return m_parentId;
}

const QString &Channel::topic() const
{
    return m_topic;
}

bool Channel::nfsw() const
{
    return m_nfsw;
}

unsigned short Channel::getMember_count() const
{
    return member_count;
}

unsigned short Channel::getMessage_count() const
{
    return message_count;
}
