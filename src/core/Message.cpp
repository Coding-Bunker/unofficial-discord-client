#include "Message.hpp"

#include <QJsonArray>
void Message::unmarshal(const QJsonObject &obj)
{
    // clazy:excludeall=qt4-qstring-from-array
    m_id        = obj[QStringLiteral("id")].toString().toULongLong();
    m_guildID   = obj[QStringLiteral("guild_id?")].toString().toULongLong();
    m_channelID = obj[QStringLiteral("channel_id")].toString().toULongLong();

    const auto &authorObj{ obj["author"].toObject() };
    m_author = authorObj[QStringLiteral("username")].toString();

    m_content = obj[QStringLiteral("content")].toString();
    m_timestamp =
        QDateTime::fromString(obj[QStringLiteral("timestamp")].toString());
    m_edited_timestamp = QDateTime::fromString(
        obj[QStringLiteral("edited_timestamp")].toString());
    m_type       = static_cast<Type>(obj[QStringLiteral("type")].toInt());
    tts          = obj[QStringLiteral("tts")].toBool();
    mentions_all = obj[QStringLiteral("mentions_everyone")].toBool();
    pinned       = obj[QStringLiteral("pinned")].toBool();
    const auto &roles{ obj["mentioned_roles"].toArray() };
    // GULP!
    for (const auto &k : roles) {
        const auto &o{ k.toObject() };
        Role j{};
        j.unmarshal(o);
        mentioned_roles.emplace_back(j);
    }
    const auto &attac{ obj["attachments"].toArray() };
    // GULP! Again!
    for (const auto &k : attac) {
        const auto &o{ k.toObject() };
        Attachment b;
        b.unmarshall(o);
        attachments.emplace_back(b);
    }
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

bool Message::getPinned() const
{
    return pinned;
}

const QList<Embed> &Message::getEmbeds() const
{
    return embeds;
}

/*
const QList<Component> &Message::getAction_rows() const
{
    return action_rows;
}*/
