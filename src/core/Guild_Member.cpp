#include "Guild_Member.hpp"

#include "User.hpp"

#include <QJsonArray>
#include <QJsonDocument>

void GuildMember::unmarshal(const QJsonObject &&o)
{
    // TODO: handle user field
    /*
    if (o.contains(QStringLiteral("user"))) {
        User k;
        k.populate(QJsonDocument(o[QStringLiteral("user")].toObject()));
        m_user = std::make_unique<User>(k);
    }*/
    if (o.contains(QStringLiteral("nick")) &&
        !o[QStringLiteral("nick")].isNull())
        m_nick = o[QStringLiteral("nick")].toString();
    const auto &a{ o[QStringLiteral("roles")].toArray() };
    m_roles.reserve(a.size());
    for (const auto &r : a)
        m_roles.emplace_back(r.toString().toULongLong());
    using D     = QDateTime;
    m_join_time = D::fromString(o[QStringLiteral("joined_at")].toString());
    if (o.contains(QStringLiteral("premium_since")) &&
        !o[QStringLiteral("premium_since")].isNull())
        m_premium_join_time =
            D::fromString(o[QStringLiteral("premium_since")].toString());
    m_deaf = o[QStringLiteral("deaf")].toBool();
    m_mute = o[QStringLiteral("mute")].toBool();
    if (o.contains(QStringLiteral("pending")))
        m_pending = o[QStringLiteral("pending")].toBool();
    if (o.contains(QStringLiteral("permissions")))
        m_permissions = o[QStringLiteral("permissions")].toString();
}

optional<bool> GuildMember::pending() const
{
    return m_pending;
}

optional<QString> GuildMember::nick() const
{
    return m_nick;
}

optional<QString> GuildMember::permissions() const
{
    return m_permissions;
}

optional<QDateTime> GuildMember::premium_join_time() const
{
    return m_premium_join_time;
}

const QList<snowflake> &GuildMember::roles() const
{
    return m_roles;
}

const QDateTime &GuildMember::join_time() const
{
    return m_join_time;
}

bool GuildMember::deaf() const
{
    return m_deaf;
}

bool GuildMember::mute() const
{
    return m_mute;
}
