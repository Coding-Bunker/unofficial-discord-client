#pragma once

#include "Channel.hpp"

class Guild
{
  public:
    void unmarshal(const QJsonObject &obj);

    snowflake id() const noexcept;
    QString name() const noexcept;

    void addChannel(Channel &&c);

  private:
    snowflake m_id;
    QString m_name;
    QString m_icon;

    QVector<Channel> m_channels;
};
