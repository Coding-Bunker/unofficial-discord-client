#pragma once

#include "core/User.hpp"
#include "gui/GuildsModel.hpp"
#include "handlers/Authenticator.hpp"
#include "handlers/Requester.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

class Application : public QObject
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(GuildsModel *guildsModel READ guildsModel NOTIFY guildsModelChanged)
    // clang-format on

  public:
    explicit Application(int &argc, char **argv);

    int run();

    GuildsModel *guildsModel() const;

  signals:
    void loginSuccess();
    void guildsModelChanged();

  private:
    std::unique_ptr<QGuiApplication> m_application;
    QQmlApplicationEngine m_engine;

    User m_user;

    Authenticator m_auth;
    Requester m_req;

    std::unique_ptr<GuildsModel> m_guildsModel;
};
