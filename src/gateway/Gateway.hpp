#pragma once

//#include <QtWebSocket>
enum class Sendable_Opcode : unsigned char {
    Heartbeat = 1,
    Identify,
    Presence_Update,
    Voice_State_Update,
    Resume                = 6,
    Request_Guild_Members = 8,
};

enum class Receivable_Opcode : unsigned char {
    Dispatch,
    Heartbeat,
    Reconnect       = 7,
    Invalid_Session = 9,
    Hello,
    Heartbeat_ACK,
};

class Gateway
{
  public:
};
