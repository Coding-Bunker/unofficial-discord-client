#include "Application.hpp"

#include <QJsonDocument>
#include <QQmlContext>
#include <QSettings>

Application::Application(QQmlContext *ctx, QObject *parent) : QObject(parent)
{
    ctx->setContextProperty("qtVersion", QT_VERSION_STR);
    ctx->setContextProperty("hmi", this);
    ctx->setContextProperty("auth", &m_auth);
    ctx->setContextProperty("user", &m_user);

    connect(&m_auth, &Authenticator::authenticationSuccess, this,
            &Application::handleLoginSuccess);

    connect(&m_req, &Requester::guildsFinished, this,
            &Application::handleGuildsFinished);

    connect(&m_req, &Requester::channelFinished,
            [&](const QByteArray &data) { m_user.setChannelsForGuild(data); });

    connect(&m_req, &Requester::messagesFinished, this, [&](QByteArray data) {
        m_user.setMessagesForChannel(m_guildsModel->selectedID(), data);
    });
}

bool Application::guildModelVisible() const
{
    return m_guildModelVisible;
}

GuildsModel *Application::guildsModel() const
{
    return m_guildsModel.get();
}

void Application::loadSettings()
{
    m_settings.loadSettings();

    const auto t  = m_settings.token();
    const auto me = m_settings.meInfo();
    if (!t.isEmpty() && !me.isEmpty()) {
        handleLoginSuccess(t, QJsonDocument::fromJson(me));
    }
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
    m_guildsModel       = std::make_unique<GuildsModel>(&m_user.guilds);
    m_guildModelVisible = true;
    emit guildsModelChanged();
    m_req.requestChannels(m_user.guildIDs());

    connect(m_guildsModel->channelsModel(), &ChannelsModel::requestMessages,
            &m_req, &Requester::requestMessages);

    connect(&m_user, &User::messagesUpdated, m_guildsModel.get(),
            &GuildsModel::updateMessages);
}
