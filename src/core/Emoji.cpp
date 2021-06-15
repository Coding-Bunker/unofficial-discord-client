#include "Emoji.hpp"

#include <QJsonDocument>

snowflake Emoji::id() const
{
    return m_id;
}

const QString &Emoji::name() const
{
    return m_name;
}

optional<User> &Emoji::user()
{
    return m_user;
}

optional<bool> Emoji::require_colons() const
{
    return m_require_colons;
}

optional<bool> Emoji::managed() const
{
    return m_managed;
}

optional<bool> Emoji::animated() const
{
    return m_animated;
}

optional<bool> Emoji::available() const
{
    return m_available;
}

void Emoji::unmarshal(const QJsonObject &o)
{
    m_id = o["id"].toString().toULongLong();
    if (!o["name"].isNull())
        m_name = o["name"].toString();
    if (o.contains("require_colons"))
        m_require_colons = o["require_colons"].toBool();
    if (o.contains("managed"))
        m_managed = o["managed"].toBool();
    if (o.contains("animated"))
        m_animated = o["animated"].toBool();
    if (o.contains("available"))
        m_available = o["available"].toBool();
    if (o.contains("user")) {
        const auto &t{ QJsonDocument(o["user"].toObject()) };
        User u;
        u.populate(t);
        m_user.emplace(u);
    }
}
