#pragma once

#include <QNetworkAccessManager>

class Requester : public QObject
{
    Q_OBJECT

  public:
    explicit Requester(QObject *parent = nullptr);

    void setToken(const QString &token);

  public:
    void requestGuilds();

  signals:
    void finished(const QString response);

  private slots:
    void response();

  private:
    QString m_token;
    QNetworkAccessManager m_nam;

    void request(const QString &api);
};
