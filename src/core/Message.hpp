#pragma once

#include "Types.hpp"

#include <QDateTime>
#include <QJsonObject>

class Message
{
  public:
    void unmarshal(const QJsonObject &obj);

    enum class Type {
        DEFAULT,
        RECIPIENT_ADD,
        RECIPIENT_REMOVE,
        CALL,
        CHANNEL_NAME_CHANGE,
        CHANNEL_ICON_CHANGE,
        CHANNEL_PINNED_MESSAGE,
        GUILD_MEMBER_JOIN,
        USER_PREMIUM_GUILD_SUBSCRIPTION,
        USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1,
        USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2,
        USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3,
        CHANNEL_FOLLOW_ADD,
        GUILD_DISCOVERY_DISQUALIFIED = 14,
        GUILD_DISCOVERY_REQUALIFIED,
        GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING,
        GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING,
        THREAD_CREATED,
        REPLY,
        APPLICATION_COMMAND,
        THREAD_STARTER_MESSAGE,
        GUILD_INVITE_REMINDER
    };

    snowflake guildID() const;

    snowflake channelID() const;

    QDateTime timestamp() const;

    QString content() const;

    QString author() const;

  private:
    snowflake m_id;
    snowflake m_channelID;
    snowflake m_guildID;
    QString m_author;
    QString m_content;
    QDateTime m_timestamp;
    Type m_type;
};
