#pragma once

#include "Authenticator.hpp"

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
    Authenticator m_auth;
};
