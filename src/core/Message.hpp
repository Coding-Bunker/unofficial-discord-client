#pragma once

#include "Attachment.hpp"
#include "Component.hpp"
#include "Embed.hpp"
#include "Role.hpp"
#include "Types.hpp"

#include <QDateTime>
#include <QJsonObject>
#include <optional>

using std::optional;

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

    optional<snowflake> guildID() const;

    snowflake channelID() const;

    QDateTime timestamp() const;

    QString content() const;

    QString author() const;

    snowflake id() const;

    bool getPinned() const;

    const QList<Embed> &getEmbeds() const;
    const QDateTime& edited_timestamp() const;
    Type type() const;
    bool getTts() const;
    bool getMentions_all() const;
    const QList<Role>& getMentioned_roles() const;
    const QList<Attachment> &getAttachments() const;

  private:
    snowflake m_id;
    snowflake m_channelID;
    optional<snowflake> m_guildID;
    QString m_author;
    QString m_content;
    QDateTime m_timestamp, m_edited_timestamp;
    Type m_type;
    bool tts, mentions_all, pinned;
    QList<Role> mentioned_roles;
    QList<Attachment> attachments;
    QList<Embed> embeds;
};
