#include "Message.hpp"

void Message::unmarshal(const QJsonObject &obj)
{
    m_id        = obj.value("id").toString().toULongLong();
    m_guildID   = obj.value("guild_id?").toString().toULongLong();
    m_channelID = obj.value("channel_id").toString().toULongLong();

    const auto authorObj = obj.value("author").toObject();
    m_author             = authorObj.value("username").toString();

    m_content   = obj.value("content").toString();
    m_timestamp = QDateTime::fromString(obj.value("timestamp").toString());
    m_type      = static_cast<Type>(obj.value("type").toInt());
}

snowflake Message::guildID() const
{
    return m_guildID;
}

snowflake Message::channelID() const
{
    return m_channelID;
}

QDateTime Message::timestamp() const
{
    return m_timestamp;
}

QString Message::content() const
{
    return m_content;
}

QString Message::author() const
{
    return m_author;
}
