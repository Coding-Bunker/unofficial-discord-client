#pragma once

#include "Channel.hpp"

class Guild
{
  public:
    void unmarshal(const QJsonObject &obj);

    snowflake id() const noexcept;
    QString name() const noexcept;
    QString iconHash() const noexcept;
    QByteArray iconBase64() const noexcept;

    void addChannel(Channel &&c);

    void addMessageToChannel(Message &&m);

    void setIconBase64(QByteArray &&data);

    QList<Channel> channels;

  private:
    snowflake m_id;
    QString m_name;
    QString m_iconHash;
    QByteArray m_iconBase64;
};
