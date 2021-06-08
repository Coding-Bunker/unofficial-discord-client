#include "Guild.hpp"

#include <QJsonObject>

void Guild::unmarshal(const QJsonObject &obj)
{
    m_id       = obj.value("id").toString().toULongLong();
    m_name     = obj.value("name").toString();
    m_iconHash = obj.value("icon").toString();
}

snowflake Guild::id() const noexcept
{
    return m_id;
}

QString Guild::name() const noexcept
{
    return m_name;
}

QString Guild::iconHash() const noexcept
{
    return m_iconHash;
}

const QByteArray &Guild::icondata() const noexcept
{
    return m_icondata;
}

void Guild::addChannel(Channel &&c)
{
    // FIXME: for now I just add text channel, should handle categories and
    // voice

    // Clang does not support "using enum" yet, so kludge here is needed
    using Type = Channel::Type;
    switch (c.type()) {
        case Type::GUILD_TEXT:
            channels.push_back(c);
            break;
        case Type::GROUP_DM:
            break;
        case Type::GUILD_CATEGORY:
            break;
        case Type::GUILD_NEWS:
            break;
        case Type::GUILD_STORE:
            break;
        case Type::GUILD_VOICE:
            break;
        case Type::DM:
            break;
    }

    std::sort(channels.begin(), channels.end(),
              [](const Channel &lh, const Channel &rh) {
                  return lh.position() < rh.position();
              });
}

void Guild::addMessageToChannel(Message &&m)
{
    const auto it =
        std::find_if(channels.begin(), channels.end(),
                     [&](const Channel &c) { return c.id() == m.channelID(); });

    if (it == channels.end()) {
        qWarning() << "channelID not found for message";
        return;
    }

    const auto pos = std::distance(channels.begin(), it);
    channels[pos].messages.push_back(std::move(m));
}

void Guild::setIconBase64(QByteArray &&data)
{
    m_icondata = data;
}

snowflake Guild::public_updates_channel_id() const
{
    return m_public_updates_channel_id;
}

const QString &Guild::splashHash() const
{
    return m_splashHash;
}

const QString &Guild::preferredlocale() const
{
    return m_preferredlocale;
}

NSFW_level Guild::nsfwlvl() const
{
    return m_nsfwlvl;
}

snowflake Guild::mfalvl() const
{
    return m_mfalvl;
}

void Guild::setMfalvl(snowflake newMfalvl)
{
    m_mfalvl = newMfalvl;
}

snowflake Guild::ownerid() const
{
    return m_ownerid;
}

const QString &Guild::desc() const
{
    return m_desc;
}

const QString &Guild::vanity_url() const
{
    return m_vanity_url;
}

Veri_level Guild::verilvl() const
{
    return m_verilvl;
}

Explicit_Filter_level Guild::explilvl() const
{
    return m_explilvl;
}

bool Guild::is_only_mentioned() const
{
    return only_mentioned;
}

const QVariantList &Guild::roles() const
{
    return m_roles;
}
