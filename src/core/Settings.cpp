#include "Settings.hpp"

#include <QSettings>

Settings::Settings(QObject *parent) : QObject(parent) {}

void Settings::loadSettings()
{
    QSettings settings(QSettings::Format::NativeFormat,
                       QSettings::Scope::UserScope,
                       "unofficial-discord-client");
    const auto token = settings.value(SettingsCategory::token);
    if (!token.isValid() || token.isNull()) {
        return;
    }

    m_token  = token.toString();
    m_meInfo = settings.value(SettingsCategory::meInfo).toByteArray();
}

QString Settings::token() const noexcept
{
    return m_token;
}

QByteArray Settings::meInfo() const noexcept
{
    return m_meInfo;
}
