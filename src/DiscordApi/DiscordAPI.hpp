#pragma once

#include <QString>

namespace DiscordAPI
{
const QString clientId     = "740334165651882036";
const QString clientSecret = "og4kFEYYimJCaFn0v9R7mIPg45ciTRLL";

const QByteArray fakeBrowserUserAgent =
    "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; "
    "rv:82.0) Gecko/20100101 Firefox/82.0";

const QString baseURL = "https://discord.com/api/v6";

const QString auth  = baseURL + "/auth";
const QString login = auth + "/login";
const QString mfa   = auth + "/mfa/totp";

const QString me       = baseURL + "/users/@me";
const QString guilds   = me + "/guilds";
const QString channels = baseURL + "/guilds/%1/channels";

namespace DiscordTags
{
const QString access_token  = "access_token";
const QString expires_in    = "expires_in";
const QString refresh_token = "refresh_token";
} // namespace DiscordTags

} // namespace DiscordAPI
