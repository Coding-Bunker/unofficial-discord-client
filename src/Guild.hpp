#pragma once

#include <QString>

class Guild
{
  public:
    void setId(const QString &id);

  private:
    QString m_id;
    QString m_name;
    QString m_icon;
};
