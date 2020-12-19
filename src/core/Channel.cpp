#include "Channel.hpp"

void Channel::unmarshal(const QJsonObject &obj)
{
    m_id       = obj.value("id").toString().toULongLong();
    m_name     = obj.value("name").toString();
    m_nfsw     = obj.value("nfwm").toBool();
    m_parentId = obj.value("parent_id").toString().toULongLong();
    m_guildId  = obj.value("guild_id").toString().toULongLong();
    m_position = obj.value("position").toInt();
    m_type     = static_cast<Type>(obj.value("type").toInt());
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
