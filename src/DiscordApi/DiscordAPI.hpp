#pragma once

#include <QString>

// clang-format off
namespace DiscordAPI
{

static const auto fakeBrowserUserAgent = "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:82.0) Gecko/20100101 Firefox/82.0";

static const QString baseURL      = QStringLiteral("https://discord.com/api/v9");
static const QString baseImageURL = QStringLiteral("https://cdn.discordapp.com");

static const QString auth  = baseURL + QStringLiteral("/auth");
static const QString login = auth + QStringLiteral("/login");
static const QString mfa   = auth + QStringLiteral("/mfa/totp");

static const QString me        = baseURL + QStringLiteral("/users/@me");
static const QString guilds    = me + QStringLiteral("/guilds");
static const QString guildIcon = baseImageURL + QStringLiteral("/icons/%1/%2.png");
static const QString channels  = baseURL + QStringLiteral("/guilds/%1/channels");

static const QString messages       = baseURL + QStringLiteral("/channels/%1/messages");

static const QString gatewayVersion = QStringLiteral("9");
static const QString gateway        = baseURL + QStringLiteral("/gateway");

namespace DiscordTags
{
static const QString access_token  = QStringLiteral("access_token");
static const QString expires_in    = QStringLiteral("expires_in");
static const QString refresh_token = QStringLiteral("refresh_token");
} // namespace DiscordTags

} // namespace DiscordAPI

// clang-format on
