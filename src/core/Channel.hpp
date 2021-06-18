#pragma once

#include "Message.hpp"
#include "Types.hpp"

#include <QJsonObject>

class Channel
{
  public:
    void unmarshal(const QJsonObject &obj);

    snowflake id() const;
    QString name() const;

    snowflake guildId() const;
    int position() const;

    enum class Type {
        GUILD_TEXT,     // a text channel within a server
        DM,             // a direct message between users
        GUILD_VOICE,    // a voice channel within a server
        GROUP_DM,       // a direct message between multiple users
        GUILD_CATEGORY, // an organizational category that contains up to 50
                        // channels
        GUILD_NEWS,  // a channel that users can follow and crosspost into their
                     // own server
        GUILD_STORE, // a channel in which game developers can sell their game
                     // on Discord
    };

    Type type() const;

    QList<Message> messages;

    snowflake last_message_id() const;
    snowflake parentId() const;
    const QString &topic() const;
    bool nfsw() const;
    unsigned short getMember_count() const;
    unsigned short getMessage_count() const;

  private:
    snowflake m_id, m_last_message_id, m_guildId, m_parentId;
    QString m_name, m_topic;
    bool m_nfsw;
    int m_position;
    unsigned rate_limit_per_user;
    unsigned short member_count, message_count;
    Type m_type;
};
