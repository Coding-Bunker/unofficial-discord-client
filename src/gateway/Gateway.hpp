#pragma once

//#include <QtWebSocket>

#include "common.hpp"

#include <QTimer>
#include <QUrl>

// TODO: handle ETF encoding
static QUrl ws_url;

class Gateway : QObject
{
    Q_OBJECT
    unsigned short heartbeat_interval;
    QTimer *m_timer;
    Payload_Base *m_payload;
    QString session_id;

  public:
    Gateway();
    ~Gateway();
    void heartbeat();
    void identify();
    void resume();
};
