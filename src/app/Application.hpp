#pragma once

#include "core/User.hpp"
#include "handlers/Authenticator.hpp"
#include "handlers/Requester.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <memory>

class Application
{
  public:
    explicit Application(int &argc, char **argv);

    int run();

  private:
    std::unique_ptr<QGuiApplication> m_application;
    QQmlApplicationEngine m_engine;

    User m_user;

    Authenticator m_auth;
    Requester m_req;
};
