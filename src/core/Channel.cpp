#include "Channel.hpp"

void Channel::unmarshal(const QJsonObject &obj)
{
    m_id              = obj.value("id").toString().toULongLong();
    m_name            = obj.value("name").toString();
    m_nfsw            = obj.value("nfwm").toBool();
    m_parentId        = obj.value("parent_id").toString().toULongLong();
    m_guildId         = obj.value("guild_id").toString().toULongLong();
    m_position        = obj.value("position").toInt();
    m_topic           = obj.value("topic").toString();
    m_last_message_id = obj.value("last_message_id").toString().toULongLong();
    rate_limit_per_user =
        obj.value("rate_limit_per_user").toString().toUShort();
    m_type        = static_cast<Type>(obj.value("type").toInt());
    message_count = obj.value("message_count").toString().toUShort();
    member_count  = obj.value("member_count").toString().toUShort();
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
