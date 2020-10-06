#pragma once

#include "Types.hpp"

#include <QString>
#include <QtDebug>

class Guild
{
  public:
    void setId(snowflake id);
    void setName(const QString &name);

    QString name() const noexcept;

    friend QDebug operator<<(QDebug dbg, const Guild &u);

  private:
    snowflake m_id;
    QString m_name;
    QString m_icon;
};
