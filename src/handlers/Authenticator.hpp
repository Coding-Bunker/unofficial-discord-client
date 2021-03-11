#pragma once

#include <QNetworkAccessManager>

class Authenticator : public QObject
{
    Q_OBJECT

  public:
    Q_INVOKABLE void requestLogin(QString email, QString pass, QString twoFA);

  signals:
    void authenticationSuccess(const QString &token, const QJsonDocument &doc);
    void saveSettings(QString token, QByteArray meInfo);

  private:
    QNetworkAccessManager m_nam;
    QString m_token;

    void handleLoginResponse(QString body, QString twoFA);
    void request2FA(QString ticket, QString mfa);
    void handlePersonInfo();
};
