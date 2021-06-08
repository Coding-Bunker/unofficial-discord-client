#include "Guild.hpp"

#include <QJsonArray>
#include <QJsonObject>
#include <utility>

void Guild::unmarshal(const QJsonObject &obj)
{
    Guild_Base::unmarshal(obj);
    only_mentioned =
        obj[QStringLiteral("default_message_notifications")].toInt();
    m_mfa_required = obj[QStringLiteral("mfa_level")].toInt();
    if (!obj[QStringLiteral("banner")].isNull())
        m_bannerhash = obj[QStringLiteral("banner")].toString();
    if (!obj[QStringLiteral("vanity_url")].isNull())
        m_vanity_url = obj[QStringLiteral("vanity_url")].toString();
    m_nsfwlvl =
        static_cast<NSFW_level>(obj[QStringLiteral("nsfw_level")].toInt());
    m_explilvl = static_cast<Explicit_Filter_level>(
        obj[QStringLiteral("explicit_content_filter")].toInt());
    m_verilvl =
        static_cast<Veri_level>(obj[QStringLiteral("mfa_level")].toInt());
    m_public_updates_channel_id =
        obj[QStringLiteral("public_updates_channel_id")]
            .toString()
            .toULongLong();
    m_preferredlocale = obj[QStringLiteral("preferred_locale")].toString();

    m_roles.reserve(obj[QStringLiteral("roles")].toArray().size());
    auto tmp{ obj[QStringLiteral("roles")].toArray() };
    for (const auto &&f : std::as_const(tmp)) {
        const auto &&e{ f.toObject() };
        Role j;
        j.unmarshal(e);
        m_roles.emplace_back(j);
    }
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
        case Type::GUILD_NEWS_THREAD:
            break;
        case Type::GUILD_PUBLIC_THREAD:
            break;
        case Type::GUILD_PRIVATE_THREAD:
            break;
        case Type::GUILD_STAGE_VOICE:
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
