#pragma once
#include <QString>
#include <QUuid>
#include <variant>

struct Sending {
    QUuid id;
    QString type;
    QString allow;
    QString deny;
};

struct Receiving {
    QUuid id;
    QString type;
    int allow;
    QString allow_new;
    int deny;
    QString deny_new;
};

using Overwrite = std::variant<Sending, Receiving>;
