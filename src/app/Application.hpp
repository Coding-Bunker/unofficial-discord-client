#pragma once

#include "core/Settings.hpp"
#include "core/User.hpp"
#include "gui/GuildsModel.hpp"
#include "gui/SettingsModel.hpp"
#include "handlers/Authenticator.hpp"
#include "handlers/Requester.hpp"

#include <memory>

class QQmlContext;

class Application : public QObject
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(bool guildModelVisible READ guildModelVisible NOTIFY guildsModelChanged)
    Q_PROPERTY(GuildsModel *guildsModel READ guildsModel NOTIFY guildsModelChanged)
    // clang-format on

  public:
    explicit Application(QQmlContext *ctx, QObject *parent = nullptr);

    bool guildModelVisible() const;
    GuildsModel *guildsModel() const;

    void loadSettings();
    Q_INVOKABLE void saveSettings();

  signals:
    void loginSuccess();
    void showError(const QString &title, const QString &message);
    void guildsModelChanged();

  private slots:
    void handleLoginSuccess(const QString &token, const QJsonDocument &meInfo);
    void handleLoginFailed(const QString &errorNumber, const QString &errorMessage);
    void handleGuildsFinished(const QByteArray &data);
    void saveAuthSettings(QString token, QByteArray meInfo);
    void handleGuildsIcons(snowflake guildID, QByteArray imgBase64);

  private:
    bool m_guildModelVisible{ false };
    User m_user;

    Authenticator m_auth;
    Requester m_req;

    std::unique_ptr<GuildsModel> m_guildsModel;

    Settings m_settings;
    SettingsModel m_settingsModel;

    void updateUI();
};
