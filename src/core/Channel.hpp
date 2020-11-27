#pragma once

#include "Types.hpp"

#include <QJsonObject>

class Channel
{
  public:
    void unmarshal(const QJsonObject &obj);

    QString name() const;

    snowflake guildId() const;

  private:
    snowflake m_id;
    QString m_name;
    bool m_nfsw;
    snowflake m_guildId;
    snowflake m_parentId;
    int m_position;
    // TODO: implement type of channel before add
};
