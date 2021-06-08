#include "User.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <utility>

void User::populate(const QJsonDocument &doc)
{
    // clazy:excludeall=qt4-qstring-from-array
    const auto &info{ doc.object() };

    m_id            = info[QStringLiteral("id")].toString().toULongLong();
    m_username      = info[QStringLiteral("username")].toString();
    m_avatar        = info[QStringLiteral("avatar")].toString();
    m_discriminator = info[QStringLiteral("discriminator")].toString();

    emit usernameChanged();
}

QString User::username() const
{
    return m_username;
}

void User::setGuilds(const QByteArray &data)
{
    const auto &array{ QJsonDocument::fromJson(data).array() };
    guilds.reserve(array.size());
    for (const auto &a : array) {
        const auto &obj{ a.toObject() };
        Guild g;
        g.unmarshal(obj);
        guilds.emplace_back(g);
    }
}

QList<snowflake> User::guildIDs() const noexcept
{
    QList<snowflake> ret(guilds.size());
    for (const auto &g : guilds) {
        ret.emplace_back(g.id());
    }
    return ret;
}

using std::pair;
QList<pair<snowflake, QString>> User::pairsGuildIDandHashImg() noexcept
{
    QList<pair<snowflake, QString>> ret;
    for (const auto &g : guilds) {
        ret.emplace_back(
            std::make_pair<snowflake, QString>(g.id(), g.iconHash()));
    }

    return ret;
}

void User::setChannelsForGuild(const QByteArray &data)
{
    const auto &obj{ QJsonDocument::fromJson(data).array() };
    for (const auto &o : obj) {
        const auto &ch{ o.toObject() };
        Channel c;
        c.unmarshal(ch);
        const auto &it{ std::find_if(
            guilds.begin(), guilds.end(),
            [&](const Guild &g) { return c.guildId() == g.id(); }) };
        if (it == guilds.end()) {
            qWarning() << "guild id not found for channel " << *c.name();
            continue;
        }

        const auto pos = std::distance(guilds.begin(), it);
        guilds[pos].addChannel(std::move(c));
    }
}

void User::setMessagesForChannel(snowflake guildID, const QByteArray &data)
{
    const auto obj = QJsonDocument::fromJson(data).array();
    for (const auto &o : obj) {
        const auto msg = o.toObject();
        Message m;
        m.unmarshal(msg);
        addMessageToGuild(guildID, std::move(m));
    }

    emit messagesUpdated();
}

void User::setIconBase64(snowflake guildID, QByteArray &&data)
{
    auto it = std::find_if(guilds.begin(), guilds.end(),
                           [&](const Guild &g) { return guildID == g.id(); });

    if (it == guilds.end()) {
        qWarning() << "guild id not found";
        return;
    }

    const auto pos = std::distance(guilds.begin(), it);
    guilds[pos].setIconBase64(std::move(data));
}

void User::addMessageToGuild(snowflake guildID, Message &&m)
{
    const auto it =
        std::find_if(guilds.begin(), guilds.end(),
                     [&](const Guild &g) { return g.id() == guildID; });
    if (it == guilds.end()) {
        qWarning() << "guildID not found for message";
        return;
    }

    it->addMessageToChannel(std::move(m));
}

QDebug operator<<(QDebug dbg, const User &u)
{
    dbg.nospace() << u.m_id << u.m_username;
    return dbg.maybeSpace();
}
