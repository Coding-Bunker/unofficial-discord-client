#pragma once

#include <QNetworkAccessManager>
#include <QTcpServer>

class Authenticator : public QObject
{
    Q_OBJECT

  public:
    Authenticator(QObject *parent = nullptr);
    ~Authenticator() override;

  public slots:
    void requestLogin();

  private slots:
    void newConnectionOnLocalServer();
    void readDataFromSocket();
    void tokenResponse();
    void infoResponse();

  private:
    void requestToken();
    void requestMeInfo();

  private:
    QTcpServer m_localServer;
    QString m_codeGrant;
    QString m_token;
    QString m_refreshToken;
    int m_expireSeconds;

    QNetworkAccessManager m_nam;
};
