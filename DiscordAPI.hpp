#pragma once

#include <QString>

namespace DiscordAPI
{
const QString baseURL      = "https://discord.com/api";
const QString authorize    = baseURL + "/oauth2/authorize";
const QString clientId     = "740334165651882036";
const QString clientSecret = "og4kFEYYimJCaFn0v9R7mIPg45ciTRLL";
const QString login        = baseURL + "/auth/login";
const QString token        = baseURL + "/oauth2/token";

namespace DiscordTags
{
const QString access_token  = "access_token";
const QString expires_in    = "expires_in";
const QString refresh_token = "refresh_token";
} // namespace DiscordTags

} // namespace DiscordAPI
