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

    enum Type {
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

    void addMessage(Message &&m);

  private:
    snowflake m_id;
    QString m_name;
    bool m_nfsw;
    snowflake m_guildId;
    snowflake m_parentId;
    int m_position;
    Type m_type;

    QList<Message> m_messages;
};
