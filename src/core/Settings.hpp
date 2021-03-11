#pragma once

#include <QObject>

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

  private:
    const QString m_settingsFilename = "unofficial-discord-client";

    QString m_token;
    QByteArray m_meInfo;
};
