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
    void guildsFinished(const QJsonArray &array);

  private slots:
    void handleGuilds(QVariant dummy);

  private:
    QString m_token;
    QNetworkAccessManager m_nam;

    template<typename T> void request(const QString &api, T callback);
};
