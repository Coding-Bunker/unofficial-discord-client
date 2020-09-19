#pragma once

#include <QString>
#include <QtDebug>

class Guild
{
  public:
    void setId(const QString &id);
    void setName(const QString &name);

    QString name() const noexcept;

    friend QDebug operator<<(QDebug dbg, const Guild &u);

  private:
    QString m_id;
    QString m_name;
    QString m_icon;
};
