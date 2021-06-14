#pragma once

#include "Attachment.hpp"
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

    enum Type {
        DEFAULT                                = 0,
        RECIPIENT_ADD                          = 1,
        RECIPIENT_REMOVE                       = 2,
        CALL                                   = 3,
        CHANNEL_NAME_CHANGE                    = 4,
        CHANNEL_ICON_CHANGE                    = 5,
        CHANNEL_PINNED_MESSAGE                 = 6,
        GUILD_MEMBER_JOIN                      = 7,
        USER_PREMIUM_GUILD_SUBSCRIPTION        = 8,
        USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
        USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
        USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
        CHANNEL_FOLLOW_ADD                     = 12,
        GUILD_DISCOVERY_DISQUALIFIED           = 14,
        GUILD_DISCOVERY_REQUALIFIED            = 15,
        REPLY                                  = 19,
    };

    optional<snowflake> guildID() const;

    snowflake channelID() const;

    QDateTime timestamp() const;

    QString content() const;

    QString author() const;

    snowflake id() const;
    const QDateTime &edited_timestamp() const;
    Type type() const;
    bool getTts() const;
    bool getMentions_all() const;
    const QList<Role> &getMentioned_roles() const;
    const QList<Attachment> &getAttachments() const;

<<<<<<< HEAD
=======
    bool getPinned() const;

    const QList<Embed> &getEmbeds() const;

>>>>>>> b44681e (Follow advice from clazy: make string arguments to Qt functions QStringLiterals.)
  private:
    snowflake m_id;
    snowflake m_channelID;
    optional<snowflake> m_guildID;
    QString m_author;
    QString m_content;
    QDateTime m_timestamp, m_edited_timestamp;
    Type m_type;
    bool tts, mentions_all;
    QList<Role> mentioned_roles;
    QList<Attachment> attachments;
    QList<Embed> embeds;
};
