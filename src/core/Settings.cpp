#include "Settings.hpp"

#include <QSettings>

namespace SettingsCategory
{
const QString token  = "auth/token";
const QString meInfo = "auth/meInfo";

const QString guidsView = "UI/guildsView";

} // namespace SettingsCategory

Settings::Settings(QObject *parent) : QObject(parent)
{
    m_parameters.push_back({
        "Show guilds view with:",
        { "text", "icon" },
        0,
        UserSettingPOD::ComboBox,
        SettingsCategory::guidsView,
    });
}

void Settings::loadSettings()
{
    QSettings settings(QSettings::Format::NativeFormat,
                       QSettings::Scope::UserScope, m_settingsFilename);
    const auto token = settings.value(SettingsCategory::token);
    if (token.isValid() && !token.isNull()) {
        m_token  = token.toString();
        m_meInfo = settings.value(SettingsCategory::meInfo).toByteArray();
    }

    m_parameters[0].value = settings.value(SettingsCategory::guidsView).toInt();
}

void Settings::save() const
{
    QSettings settings(QSettings::Format::NativeFormat,
                       QSettings::Scope::UserScope, m_settingsFilename);

    for (const auto &s : m_parameters) {
        settings.setValue(s.persistentLabel, s.value);
    }

    settings.sync();
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
