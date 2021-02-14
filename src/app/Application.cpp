#include "Application.hpp"

#include <QJsonDocument>
#include <QQmlContext>
#include <QQuickStyle>
#include <QSettings>

Application::Application(int &argc, char **argv) :
    m_application{ std::make_unique<QGuiApplication>(argc, argv) }
{
    m_application->setAttribute(Qt::AA_EnableHighDpiScaling);
    m_application->setApplicationName("unofficial-discord-client");
    m_application->setOrganizationName("Coding Bunker");
    m_application->setApplicationVersion("0.0.1");

    QQuickStyle::setStyle("Material");

    const auto rc = m_engine.rootContext();

    rc->setContextProperty("qtVersion", QT_VERSION_STR);
    rc->setContextProperty("hmi", this);
    rc->setContextProperty("auth", &m_auth);
    rc->setContextProperty("user", &m_user);

    m_engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    connect(&m_auth, &Authenticator::authenticationSuccess, this,
            &Application::handleLoginSuccess);

    connect(&m_req, &Requester::guildsFinished, this,
            &Application::handleGuildsFinished);

    connect(&m_req, &Requester::channelFinished,
            [&](const QByteArray &data) { m_user.setChannelsForGuild(data); });

    connect(&m_req, &Requester::messagesFinished, this, [&](QByteArray data) {
        m_user.setMessagesForChannel(m_guildsModel->selectedID(), data);
    });

    loadSettings();
}

int Application::run()
{
    return m_application->exec();
}

GuildsModel *Application::guildsModel() const
{
    return m_guildsModel.get();
}

void Application::handleLoginSuccess(const QString &token,
                                     const QJsonDocument &meInfo)
{
    emit loginSuccess();
    m_req.setToken(token);
    m_user.populate(meInfo);
    m_req.requestGuilds();
}

void Application::handleGuildsFinished(const QByteArray &data)
{
    m_user.setGuilds(data);
    m_guildsModel = std::make_unique<GuildsModel>(&m_user.guilds);
    emit guildsModelChanged();
    m_req.requestChannels(m_user.guildIDs());

    connect(m_guildsModel->channelsModel(), &ChannelsModel::requestMessages,
            &m_req, &Requester::requestMessages);

    connect(&m_user, &User::messagesUpdated, m_guildsModel.get(),
            &GuildsModel::updateMessages);
}

void Application::loadSettings()
{
    QSettings settings(QSettings::Format::NativeFormat,
                       QSettings::Scope::UserScope,
                       "unofficial-discord-client");
    const auto token = settings.value("auth/token");
    if (!token.isValid() || token.isNull()) {
        return;
    }

    const auto info = settings.value("auth/meInfo").toByteArray();
    auto d          = QJsonDocument::fromJson(info);
    handleLoginSuccess(token.toString(), d);
}
