#pragma once

#include "Types.hpp"

#include <QJsonObject>
#include <QString>
#include <optional>

using std::optional;
class Role
{
  public:
    void unmarshal(const QJsonObject &obj);
    snowflake id() const;
    const QString &name() const;
    const QString &permissions() const;
    bool hoisted() const;
    bool managed() const;
    bool mentionable() const;
    // XXX: cludge
    class Tags
    {
        optional<snowflake> id, integration_id;
        Tags(snowflake id, snowflake inte) : id(id), integration_id(inte) {}

      public:
        Tags(optional<snowflake> id, optional<snowflake> inte) :
            id(id), integration_id(inte)
        {
        }
    };
    optional<Tags> getTags() const;
    // Needed to construct from JSON within array of role objects found in user
    Role(snowflake id, QString name, unsigned long color, bool pinned,
         unsigned position, QString perm, bool manag, bool menti,
         optional<Tags> t) :
        m_id(id),
        m_name(name), m_permissions(perm), m_hoisted(pinned),
        m_position(position), m_managed(manag), m_mentionable(menti), m_tags(t),
        m_color(color)
    {
    }
    Role() = default;

    unsigned long position() const;

  private:
    snowflake m_id;
    QString m_name, m_permissions;
    unsigned m_color{ 0 }, m_position;
    bool m_hoisted, m_managed, m_mentionable;

    optional<Tags> m_tags;
};
