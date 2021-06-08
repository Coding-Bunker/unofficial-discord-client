#include "Message.hpp"

void Message::unmarshal(const QJsonObject &obj)
{
    m_id        = obj["id"].toString().toULongLong();
    m_guildID   = obj["guild_id?"].toString().toULongLong();
    m_channelID = obj["channel_id"].toString().toULongLong();

    const auto authorObj = obj["author"].toObject();
    m_author             = authorObj["username"].toString();

    m_content   = obj["content"].toString();
    m_timestamp = QDateTime::fromString(obj["timestamp"].toString());
    m_type      = static_cast<Type>(obj["type"].toInt());
}

optional<snowflake> Message::guildID() const
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

snowflake Message::id() const
{
    return m_id;
}

const QDateTime &Message::edited_timestamp() const
{
    return m_edited_timestamp;
}

using Type = Message::Type;
Type Message::type() const
{
    return m_type;
}

bool Message::getTts() const
{
    return tts;
}

bool Message::getMentions_all() const
{
    return mentions_all;
}

const QList<Role> &Message::getMentioned_roles() const
{
    return mentioned_roles;
}

const QList<Attachment> &Message::getAttachments() const
{
    return attachments;
}
