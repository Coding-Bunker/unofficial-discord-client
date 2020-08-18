#pragma once
#include <QString>
#include <QUuid>

struct User {
    QUuid id;
    QString username;
    QString discriminator;
    QString avatar;
    bool is_bot = false;
    bool is_system false;
    bool mfa_enabled = false;
    QString locale;
    bool verified = false;
    QString email;
    int flag;
    int premium_type;
    int public_flag;
};
