#pragma once

#include <QObject>

class UserSettingPOD
{
  public:
    enum Type { ComboBox };

    QString description;
    QStringList possibleValues;
    int value;
    Type type;
    QString persistentLabel;
};

class Settings : public QObject
{
    // clang-format off
    Q_OBJECT
    // clang-format on

  public:
    Settings(QObject *parent = nullptr);

    void loadSettings();
    void save() const;
    void saveAuthSettings(QString token, QByteArray meInfo);

    QString token() const noexcept;
    QByteArray meInfo() const noexcept;

    const QVector<UserSettingPOD> &parameters() const;
    void setParameter(int indexOfParam, int valueOfChoices);

    bool guildsViewAsIcon() const noexcept;
    bool guildsIconsAsHorizontalDirection() const noexcept;

  private:
    const QString m_settingsFilename = "unofficial-discord-client";

    QString m_token;
    QByteArray m_meInfo;

    QVector<UserSettingPOD> m_parameters;
};
