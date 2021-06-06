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
