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
    optional<snowflake> parentId() const;
    const optional<QString> &topic() const;
    optional<bool> nfsw() const;
    optional<unsigned short> getMember_count() const;
    optional<unsigned short> getMessage_count() const;

  private:
    /*Only the id and type of channel object is technically guranteed to return
    values */
    snowflake m_id;

    optional<bool> m_nfsw;
    optional<QString> m_name, m_topic;
    optional<snowflake> m_guildId, m_parentId;
    optional<int> m_position;
    Type m_type;
    optional<snowflake> m_last_message_id;
    optional<unsigned short> rate_limit_per_user, message_count, member_count;
};
