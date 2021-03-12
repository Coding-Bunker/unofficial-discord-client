#pragma once

#include <QObject>

class UserSettingPOD
{
  public:
    enum Type { ComboBox };

    QString description;
    QStringList possibleValues;
    int values;
    Type type;
};

class Settings : public QObject
{
    // clang-format off
    Q_OBJECT
    // clang-format on

  public:
    Settings(QObject *parent = nullptr);

    void loadSettings();
    void saveAuthSettings(QString token, QByteArray meInfo);

    QString token() const noexcept;
    QByteArray meInfo() const noexcept;

    const QVector<UserSettingPOD> &parameters() const;

  private:
    const QString m_settingsFilename = "unofficial-discord-client";

    QString m_token;
    QByteArray m_meInfo;

    QVector<UserSettingPOD> m_parameters{
        { "Show guilds view with:",
          { "text", "icon" },
          0,
          UserSettingPOD::ComboBox },
    };
};
