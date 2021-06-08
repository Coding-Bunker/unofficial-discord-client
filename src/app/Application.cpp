#include "Application.hpp"

#include <QJsonDocument>
#include <QSettings>
#include <QtQml>

Application::Application(QQmlContext *ctx, QObject *parent) : QObject(parent)
{
    ctx->setContextProperty(QStringLiteral("qtVersion"), QT_VERSION_STR);
    ctx->setContextProperty(QStringLiteral("hmi"), this);
    ctx->setContextProperty(QStringLiteral("auth"), &m_auth);
    ctx->setContextProperty(QStringLiteral("user"), &m_user);
    ctx->setContextProperty(QStringLiteral("settingsModel"), &m_settingsModel);

    qmlRegisterUncreatableType<GuildsModel>("ui", 1, 0, "ViewMode", {});
    qmlRegisterUncreatableType<GuildsModel>("ui", 1, 0, "ViewIconDirection",
                                            {});

    connect(&m_auth, &Authenticator::authenticationSuccess, this,
            &Application::handleLoginSuccess);

    connect(&m_auth, &Authenticator::authenticationFailed, this,
            &Application::handleLoginFailed);

    connect(&m_auth, &Authenticator::saveSettings, this,
            &Application::saveAuthSettings);

    connect(&m_req, &Requester::guildsFinished, this,
            &Application::handleGuildsFinished);

    connect(&m_req, &Requester::guildIconBase64, this,
            &Application::handleGuildsIcons);

    connect(&m_req, &Requester::channelFinished,
            [&](const QByteArray &data) { m_user.setChannelsForGuild(data); });

    connect(&m_req, &Requester::messagesFinished, this,
            [&](const QByteArray &data) {
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

    m_settingsModel.setSettings(&m_settings);

    const auto t  = m_settings.token();
    const auto me = m_settings.meInfo();
    if (!t.isEmpty() && !me.isEmpty()) {
        handleLoginSuccess(t, QJsonDocument::fromJson(me));
    }
}

void Application::saveSettings()
{
    m_settings.save();
    updateUI();
}

void Application::handleLoginSuccess(const QString &token,
                                     const QJsonDocument &meInfo)
{
    emit loginSuccess();
    m_req.setToken(token);
    m_user.populate(meInfo);
    m_req.requestGuilds();
    m_req.initWebsocket();
}

void Application::handleLoginFailed(const QString &errorNumber,
                                    const QString &errorMessage)
{
    QString title = "Error(" + errorNumber + ")";
    emit showError(title, errorMessage);
}

void Application::handleGuildsFinished(const QByteArray &data)
{
    m_user.setGuilds(data);
    m_guildsModel       = std::make_unique<GuildsModel>(&m_user.guilds);
    m_guildModelVisible = true;
    emit guildsModelChanged();
    m_req.requestChannels(m_user.guildIDs());
    m_req.requestGuildsImages(m_user.pairsGuildIDandHashImg());
    updateUI();

    connect(m_guildsModel->channelsModel(), &ChannelsModel::requestMessages,
            &m_req, &Requester::requestMessages);

    connect(m_guildsModel->channelsModel(), &ChannelsModel::sendMessage, &m_req,
            &Requester::sendMessage);

    connect(&m_user, &User::messagesUpdated, m_guildsModel.get(),
            &GuildsModel::updateMessages);
}

void Application::saveAuthSettings(QString token, QByteArray meInfo)
{
    m_settings.saveAuthSettings(token, meInfo);
}

void Application::handleGuildsIcons(snowflake guildID, QByteArray imgBase64)
{
    m_user.setIconBase64(guildID, std::move(imgBase64));
    m_guildsModel->updateGuildIcon();
}

void Application::updateUI()
{
    m_guildsModel->setViewMode(m_settings.guildsViewAsIcon()
                                   ? GuildsModel::ViewMode::Icon
                                   : GuildsModel::ViewMode::Text);
    m_guildsModel->setViewIconDirection(
        m_settings.guildsIconsAsHorizontalDirection()
            ? GuildsModel::ViewIconDirection::Horizontal
            : GuildsModel::ViewIconDirection::Vertical);
}
