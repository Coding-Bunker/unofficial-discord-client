#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <optional>
#include <utility>
#include <variant>

enum Opcode : unsigned char {
    Dispatch,
    Heartbeat,
    Identify,
    Presence_Update,
    Voice_State_Update,
    Resume = 6,
    Reconnect,
    Request_Guild_Members,
    Invalid_Session,
    Hello,
    Heartbeat_ACK
};

struct Payload_Base {
    Opcode op;
    QJsonDocument body;
    std::optional<unsigned> sequence_number;
    std::optional<QByteArray> event_name;
    Payload_Base() = default;
    void serialize()
    {
        // QJsonObject k{ { "o", op }, { "d", 3 } };
    }
    /*void deserialize(const QJsonObject &o)
    {
        deserialize(std::move(o));
    }*/
    // void deserialize(const QJsonObject &&o) {}
};
