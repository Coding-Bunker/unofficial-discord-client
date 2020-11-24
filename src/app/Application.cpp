#include "Application.hpp"

#include <QQmlContext>

Application::Application(int &argc, char **argv) :
    m_application{ std::make_unique<QGuiApplication>(argc, argv) }
{
    m_application->setAttribute(Qt::AA_EnableHighDpiScaling);
    m_application->setApplicationName("unofficial-discord-client");
    m_application->setOrganizationName("Coding Bunker");
    m_application->setApplicationVersion("0.0.1");

    const auto rc = m_engine.rootContext();

    rc->setContextProperty("qtVersion", QT_VERSION_STR);
    rc->setContextProperty("hmi", this);
    rc->setContextProperty("auth", &m_auth);
    rc->setContextProperty("user", &m_user);

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    connect(&m_auth, &Authenticator::authenticationFinished,
            [&](const QString &token, const QJsonDocument &meInfo) {
                m_req.setToken(token);
                m_user.populate(meInfo);
                m_req.requestGuilds();
            });

    connect(&m_req, &Requester::guildsFinished, [&](const QByteArray &data) {
        m_user.setGuilds(data);
        m_guildsModel = std::make_unique<GuildsModel>(m_user.guilds());
        emit guildsModelChanged();
        m_req.requestChannels(m_user.guildIDs());
    });

    connect(&m_req, &Requester::channelFinished,
            [&](const QByteArray &data) { m_user.setChannelsForGuild(data); });
}

int Application::run()
{
    return m_application->exec();
}

GuildsModel *Application::guildsModel() const
{
    return m_guildsModel.get();
}
