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

const QString &Guild::preferredlocale() const
{
    return m_preferredlocale;
}

NSFW_level Guild::nsfwlvl() const
{
    return m_nsfwlvl;
}

snowflake Guild::ownerid() const
{
    return m_ownerid;
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

bool Guild::mfa_required() const
{
    return m_mfa_required;
}

void Guild_Preview::unmarshal(const QJsonObject &&o)
{
    Guild_Base::unmarshal(o);
    m_member_count = o[QStringLiteral("approximate_member_count")].toInteger();
    m_online_count =
        o[QStringLiteral("approximate_presence_count")].toInteger();
}

const unsigned &Guild_Preview::online_count() const
{
    return m_online_count;
}

void Guild_Base::unmarshal(const QJsonObject &&obj)
{
    if (!obj[QStringLiteral("discovery_splash")].isNull())
        m_discovery_splash = obj[QStringLiteral("discovery_splash")].toString();
    if (!obj[QStringLiteral("description")].isNull())
        m_description = obj[QStringLiteral("description")].toString();
    if (!obj[QStringLiteral("icon")].isNull())
        m_iconHash = obj[QStringLiteral("icon")].toString();
    if (!obj[QStringLiteral("splash")].isNull())
        m_splash = obj[QStringLiteral("splash")].toString();
    m_id   = obj[QStringLiteral("id")].toString().toULongLong();
    m_name = obj[QStringLiteral("name")].toString();

    auto tmp{ obj[QStringLiteral("features")].toArray() };
    m_features.reserve(obj[QStringLiteral("features")].toArray().size());
    m_custom_emojis.reserve(obj[QStringLiteral("emojis")].toArray().size());
    for (const auto &&f : tmp)
        m_features.emplace_back(guild_features_map[qPrintable(f.toString())]);
    tmp = obj[QStringLiteral("emojis")].toArray();
    for (const auto &&f : std::as_const(tmp)) {
        const auto &&e{ f.toObject() };
        Emoji j;
        j.unmarshal(e);
        m_custom_emojis.emplace_back(j);
    }
}

snowflake Guild_Base::id() const
{
    return m_id;
}

const QString &Guild_Base::name() const
{
    return m_name;
}

QString Guild_Base::iconHash() const
{
    return m_iconHash;
}

const QString &Guild_Base::splash() const
{
    return m_splash;
}

const QString &Guild_Base::discovery_splash() const
{
    return m_discovery_splash;
}

const QString &Guild_Base::description() const
{
    return m_description;
}

const QList<Emoji> &Guild_Base::custom_emojis() const
{
    return m_custom_emojis;
}

const QList<Guild_Features> &Guild_Base::features() const
{
    return m_features;
}

void GuildMember::unmarshal(const QJsonObject &&o)
{
    // TODO: handle user field
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
