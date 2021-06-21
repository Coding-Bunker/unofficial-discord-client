#include "Gateway.hpp"

#include "DiscordApi/DiscordAPI.hpp"

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
// #include <QWebSocket>

Gateway::Gateway() : m_timer(new QTimer), m_payload(new Payload_Base)
{
    QNetworkAccessManager m;
    const auto reply = m.get(QNetworkRequest(DiscordAPI::gateway));
    if (reply->error()) {
        qWarning() << reply->errorString();
    }
    ws_url = reply->readAll();
    QUrlQuery q(ws_url);
    q.addQueryItem(QStringLiteral("v"), DiscordAPI::gatewayVersion);
    q.addQueryItem(QStringLiteral("enconding"), QStringLiteral("json"));
    ws_url.setQuery(q);
    // TODO: insert code to open Websocket connection

    // connect(m_timer, &QTimer::timeout, this, heartbeat());
    m_timer->start(heartbeat_interval);
}

Gateway::~Gateway()
{
    delete m_timer;
    delete m_payload;
}

void Gateway::heartbeat()
{
    m_payload->op = Heartbeat;
    QJsonValue k;
}

void Gateway::identify()
{
    m_payload->op = Identify;
    const QJsonObject &identity{
        { "token", DiscordAPI::clientSecret },
        // TODO: handle intents instead of hardcoding all
        { "intents", 0b11111111111111 },
        { "properties", QJsonObject{ { "$os", "linux" },
                                     { "$browser", "tester" },
                                     { "$device", "tester" } } }
    };
    m_payload->body = QJsonDocument(std::move(identity));
}

void Gateway::resume()
{
    m_payload->op = Resume;
    const QJsonObject &body{
        { "token", DiscordAPI::clientSecret },

    };
}
