#pragma once
#include "Constructs.hpp"

#include <QUrl>
#include <QUrlQuery>
#include <QDesktopServices>

namespace DiscordAPI{
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

} // namespace Requests
} // namespace DiscordAPI
