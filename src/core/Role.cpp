#include "Role.hpp"

void Role::unmarshal(const QJsonObject &obj)
{
    // clazy:excludeall=qt4-qstring-from-array
    m_id          = obj["id"].toString().toULongLong();
    m_name        = obj["name"].toString();
    m_permissions = obj["permissions"].toString();
    m_color       = obj["color"].toInteger();
    m_position    = obj["position"].toInteger();
    m_hoisted     = obj["hoist"].toBool();
    m_managed     = obj["managed"].toBool();
    m_mentionable = obj["mentionable"].toBool();
    if (!obj["tags"].isUndefined()) {
        const auto &t{ obj["tags"].toObject() };
        optional<snowflake> id, intid;
        if (!t["id"].isUndefined() && !t["integration_id"].isUndefined()) {
            id.emplace(t["id"].toString().toULongLong());
            intid.emplace(t["integration_id"].toString().toULongLong());
        }
        Role::Tags l(id, intid);
        m_tags = l;
    }
}

snowflake Role::id() const
{
    return m_id;
}

const QString &Role::name() const
{
    return m_name;
}

const QString &Role::permissions() const
{
    return m_permissions;
}

bool Role::hoisted() const
{
    return m_hoisted;
}

bool Role::managed() const
{
    return m_managed;
}

bool Role::mentionable() const
{
    return m_mentionable;
}

optional<Role::Tags> Role::getTags() const
{
    return m_tags;
}
