#pragma once

#include <QString>
#include <QUrl>
#include <QUrlQuery>
#include <QDesktopServices>

namespace DiscordAPI {
inline const QString baseURL = "https://discord.com/api";
inline const QString authorize = baseURL + "/oauth2/authorize";
inline const QString clientId = "740334165651882036";
inline const QString clientSecret = "og4kFEYYimJCaFn0v9R7mIPg45ciTRLL";
inline const QString login = baseURL + "/auth/login";
inline const QString token = baseURL + "/oauth2/token";

namespace Requests{
inline void login()
{
    QUrl url(DiscordAPI::authorize);
    QUrlQuery query;
    query.addQueryItem("response_type", "code");
    query.addQueryItem("client_id", DiscordAPI::clientId);
    query.addQueryItem("scope", "identify%20email");
    query.addQueryItem("redirect_uri", "http://localhost:8000");
    url.setQuery(query);
    QDesktopServices::openUrl(url);
}
} // namespacd Requests
namespace DiscordTags {
inline const QString access_token = "access_token";
inline const QString expires_in = "expires_in";
inline const QString refresh_token = "refresh_token";
} // namespace DiscordTags

} // namespace DiscordAPI
