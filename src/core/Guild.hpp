#pragma once

#include "Channel.hpp"

class Guild
{
  public:
    void unmarshal(const QJsonObject &obj);

    snowflake id() const noexcept;
    QString name() const noexcept;

    void addChannel(Channel &&c);

    void addMessageToChannel(Message &&m);

    const QList<Channel> &channels() const noexcept;

  private:
    snowflake m_id;
    QString m_name;
    QString m_icon;

    QList<Channel> m_channels;
};
