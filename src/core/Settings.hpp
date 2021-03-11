#pragma once

#include <QObject>

namespace SettingsCategory
{
const QString token  = "auth/token";
const QString meInfo = "auth/meInfo";

} // namespace SettingsCategory

class Settings : public QObject
{
    // clang-format off
    Q_OBJECT
    // clang-format on

  public:
    Settings(QObject *parent = nullptr);

    void loadSettings();

    QString token() const noexcept;
    QByteArray meInfo() const noexcept;

  private:
    QString m_token;
    QByteArray m_meInfo;
};
