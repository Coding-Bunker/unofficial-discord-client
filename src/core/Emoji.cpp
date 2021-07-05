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

// TODO: handle getters of subclass of QObject...

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
    m_id = o[QStringLiteral("id")].toString().toULongLong();
    if (!o[QStringLiteral("name")].isNull())
        m_name = o[QStringLiteral("name")].toString();
    if (o.contains(QStringLiteral("require_colons")))
        m_require_colons = o[QStringLiteral("require_colons")].toBool();
    if (o.contains(QStringLiteral("managed")))
        m_managed = o[QStringLiteral("managed")].toBool();
    if (o.contains(QStringLiteral("animated")))
        m_animated = o[QStringLiteral("animated")].toBool();
    if (o.contains(QStringLiteral("available")))
        m_available = o[QStringLiteral("available")].toBool();
    if (o.contains(QStringLiteral("user"))) {
        const auto &t{ QJsonDocument(o[QStringLiteral("user")].toObject()) };
        // TODO: handle user object
    }
}
