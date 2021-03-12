#pragma once

#include <QNetworkAccessManager>
#include <QNetworkReply>

class Authenticator : public QObject
{
    Q_OBJECT

  public:
    Q_INVOKABLE void requestLogin(QString email, QString pass, QString twoFA);

  signals:
    void authenticationSuccess(const QString &token, const QJsonDocument &doc);
    void authenticationFailed(const QString &errorCode, const QString &errorMessage);
    void saveSettings(QString token, QByteArray meInfo);

  private:
    QNetworkAccessManager m_nam;
    QString m_token;

    void handleLoginResponse(QString body, QString twoFA);
    void handleLoginFailure(QNetworkReply::NetworkError error, QString body);
    void request2FA(QString ticket, QString mfa);
    void handlePersonInfo();
};
