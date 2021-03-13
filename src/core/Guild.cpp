#include "Guild.hpp"

#include <QImage>
#include <QJsonObject>

void Guild::unmarshal(const QJsonObject &obj)
{
    m_id   = obj.value("id").toString().toULongLong();
    m_name = obj.value("name").toString();
    m_icon = obj.value("icon").toString();
}

snowflake Guild::id() const noexcept
{
    return m_id;
}

QString Guild::name() const noexcept
{
    return m_name;
}

QImage Guild::icon() const noexcept
{
    QByteArray by = QByteArray::fromBase64(m_icon.toLatin1());
    QImage image  = QImage::fromData(by, "PNG");
    return image;
}

void Guild::addChannel(Channel &&c)
{
    // FIXME: for now I just add text channel, should handle categories and
    // voice

    if (c.type() == Channel::GUILD_TEXT) {
        channels.push_back(c);
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
