#pragma once

#include "Channel.hpp"

class Guild
{
  public:
    void unmarshal(const QJsonObject &obj);

    snowflake id() const noexcept;
    QString name() const noexcept;
    QImage icon() const noexcept;

    void addChannel(Channel &&c);

    void addMessageToChannel(Message &&m);

    QList<Channel> channels;

  private:
    snowflake m_id;
    QString m_name;
    QString m_icon;
};
