#pragma once

#include "Message.hpp"
#include "Types.hpp"

#include <QJsonObject>
#include <optional>

using std::optional;

class Channel
{
  public:
    void unmarshal(const QJsonObject &obj);

    snowflake id() const;
    optional<QString> name() const;

    optional<snowflake> guildId() const;
    optional<int> position() const;

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
        GUILD_NEWS_THREAD =
            10, // a temporary sub-channel within a GUILD_NEWS channel
        GUILD_PUBLIC_THREAD,  // a temporary sub-channel within a GUILD_TEXT
                              // channel
        GUILD_PRIVATE_THREAD, // a temporary sub-channel within a GUILD_TEXT
                              // channel that is only viewable by those invited
                              // and those with the MANAGE_THREADS permission
        GUILD_STAGE_VOICE // a voice channel for hosting events with an audience
    };

    Type type() const;

    QList<Message> messages;

    optional<snowflake> last_message_id() const;
    snowflake parentId() const;
    const QString &topic() const;
    bool nfsw() const;
    unsigned short getMember_count() const;
    unsigned short getMessage_count() const;

  private:
    snowflake m_id, m_guildId, m_parentId;
    QString m_name, m_topic;
    bool m_nfsw;
    int m_position;
    unsigned short member_count, message_count;
    Type m_type;
    optional<snowflake> m_last_message_id;
    optional<unsigned short> rate_limit_per_user;
};
