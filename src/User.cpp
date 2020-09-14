#include "User.hpp"

#include <QJsonArray>
#include <QJsonObject>

void User::populate(const QJsonObject &info)
{
    m_id            = info.value("id").toString();
    m_username      = info.value("username").toString();
    m_avatar        = info.value("avatar").toString();
    m_discriminator = info.value("discriminator").toString();
}

void User::setGuilds(const QJsonArray &array)
{
    for (const auto &a : array) {
        const auto obj = a.toObject();
        Guild g;
        g.setId(obj.value("id").toString());
        m_guilds.push_back(g);
    }
}
