#include "User.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

void User::populate(const QJsonDocument &doc)
{
    const auto info = doc.object();

    m_logged        = true;
    m_id            = info.value("id").toString().toULongLong();
    m_username      = info.value("username").toString();
    m_avatar        = info.value("avatar").toString();
    m_discriminator = info.value("discriminator").toString();

    emit loggedChanged();
}

bool User::logged() const
{
    return m_logged;
}

QString User::username() const
{
    return m_username;
}

void User::setGuilds(const QByteArray &data)
{
    const auto array = QJsonDocument::fromJson(data).array();
    for (const auto &a : array) {
        const auto obj = a.toObject();
        Guild g;
        g.unmarshal(obj);
        m_guilds.push_back(g);
    }
}

const QList<Guild> &User::guilds() const noexcept
{
    return m_guilds;
}

QList<snowflake> User::guildIDs() const noexcept
{
    QList<snowflake> ret;
    for (auto g : m_guilds) {
        ret.push_back(g.id());
    }
    return ret;
}

void User::setChannelsForGuild(const QByteArray &data)
{
    const auto obj = QJsonDocument::fromJson(data).array();
    for (auto o : obj) {
        const auto ch = o.toObject();
        Channel c;
        c.unmarshal(ch);
        auto it =
            std::find_if(m_guilds.begin(), m_guilds.end(),
                         [&](const Guild &g) { return c.guildId() == g.id(); });
        if (it == m_guilds.end()) {
            qWarning() << "guild id not found for channel " << c.name();
            continue;
        }

        const auto pos = std::distance(m_guilds.begin(), it);
        m_guilds[pos].addChannel(std::move(c));
    }
}

QDebug operator<<(QDebug dbg, const User &u)
{
    dbg.nospace() << u.m_id << u.m_username;
    return dbg.maybeSpace();
}
