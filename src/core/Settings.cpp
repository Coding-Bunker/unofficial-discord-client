#include "Settings.hpp"

#include <QSettings>

namespace SettingsCategory
{
const QString token  = "auth/token";
const QString meInfo = "auth/meInfo";

} // namespace SettingsCategory

Settings::Settings(QObject *parent) : QObject(parent) {}

void Settings::loadSettings()
{
    QSettings settings(QSettings::Format::NativeFormat,
                       QSettings::Scope::UserScope, m_settingsFilename);
    const auto token = settings.value(SettingsCategory::token);
    if (!token.isValid() || token.isNull()) {
        return;
    }

    m_token  = token.toString();
    m_meInfo = settings.value(SettingsCategory::meInfo).toByteArray();
}

void Settings::saveAuthSettings(QString token, QByteArray meInfo)
{
    QSettings settings(QSettings::Format::NativeFormat,
                       QSettings::Scope::UserScope, m_settingsFilename);
    settings.setValue(SettingsCategory::token, token);
    settings.setValue(SettingsCategory::meInfo, meInfo);
    settings.sync();
}

QString Settings::token() const noexcept
{
    return m_token;
}

QByteArray Settings::meInfo() const noexcept
{
    return m_meInfo;
}

const QVector<UserSettingPOD> &Settings::parameters() const
{
    return m_parameters;
}

void Settings::setParameter(int indexOfParam, int valueOfChoices)
{
    m_parameters[indexOfParam].value = valueOfChoices;
}
