#pragma once
#include <QString>


namespace DiscordAPI{

enum class AuditLogEvent{
    GUILD_UPDATE = 1,
    CHANNEL_CREATE = 10,
    CHANNEL_UPDATE,
    CHANNEL_DELETE,
    CHANNEL_OVERWRITE_CREATE,
    CHANNEL_OVERWRITE_UPDATE,
    CHANNEL_OVERWRITE_DELETE,
    MEMBER_KICK = 20,
    MEMBER_PRUNE,
    MEMBER_BAN_ADD,
    MEMBER_BAN_REMOVE,
    MEMBER_UPDATE,
    MEMBER_ROLE_UPDATE,
    MEMBER_MOVE,
    MEMBER_DISCONNECT,
    BOT_ADD,
    ROLE_CREATE,
    ROLE_DELETE,
    INVITE_CREATE = 40,
    INVITE_UPDATE,
    INVITE_DELETE,
    WEBHOOK_CREATE = 50,
    WEBHOOK_UPDATE,
    WEBHOOK_DELETE,
    EMOJI_CREATE = 60,
    EMOJI_UPDATE,
    EMOJI_DELETE,
    MESSAGE_DELETE = 72,
    MESSAGE_BULK_DELETE,
    MESSAGE_PIN,
    MESSAGE_UNPIN,
    INTEGRATION_CREATE = 80,
    INTEGRATION_UPDATE,
    INTEGRATION_DELETE
};
inline const QString baseURL = "https://discord.com/api";
inline const QString authorize = baseURL + "/oauth2/authorize";
inline const QString clientId = "740334165651882036";
inline const QString clientSecret = "og4kFEYYimJCaFn0v9R7mIPg45ciTRLL";
inline const QString login = baseURL + "/auth/login";
inline const QString token = baseURL + "/oauth2/token";


namespace DiscordTags {
inline const QString access_token = "access_token";
inline const QString expires_in = "expires_in";
inline const QString refresh_token = "refresh_token";
} // namespace DiscordTags
}
