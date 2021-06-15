#pragma once

#include "Types.hpp"

#include <QJsonObject>
#include <QString>
#include <optional>

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
        std::optional<snowflake> m_id;
        std::optional<snowflake> m_integrationId;

      public:
        Tags(std::optional<snowflake> id, std::optional<snowflake> inte) :
            m_id{ id }, m_integrationId{ inte }
        {
        }
    };
    std::optional<Tags> getTags() const;

  private:
    snowflake m_id;
    QString m_name, m_permissions;
    unsigned m_color{ 0 }, m_position;
    bool m_hoisted, m_managed, m_mentionable;
    std::optional<Tags> m_tags;
};
