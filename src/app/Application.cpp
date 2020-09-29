#include "Application.hpp"

#include <QQmlContext>

Application::Application(int &argc, char **argv) :
    m_application{ std::make_unique<QGuiApplication>(argc, argv) }
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setApplicationName("unofficial-discord-client");
    QGuiApplication::setOrganizationName("Coding Bunker");
    QGuiApplication::setApplicationVersion("0.0.1");

    const auto rc = m_engine.rootContext();

    rc->setContextProperty("qtVersion", QT_VERSION_STR);
    rc->setContextProperty("auth", &m_auth);
    rc->setContextProperty("user", &m_user);

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QObject::connect(&m_auth, &Authenticator::authenticationFinished,
                     [&](const QString &token, const QJsonObject &meInfo) {
                         m_req.setToken(token);
                         m_user.populate(meInfo);
                     });
}

int Application::run()
{
    return m_application->exec();
}
