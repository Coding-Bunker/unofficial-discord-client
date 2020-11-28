#include "Guild.hpp"

#include <QJsonObject>

void Guild::unmarshal(const QJsonObject &obj)
{
    m_id   = obj.value("id").toString().toULongLong();
    m_name = obj.value("name").toString();
}

snowflake Guild::id() const noexcept
{
    return m_id;
}

QString Guild::name() const noexcept
{
    return m_name;
}

void Guild::addChannel(Channel &&c)
{
    // FIXME: for now I just add text channel, should handle categories and
    // voice

    if (c.type() == Channel::GUILD_TEXT) {
        m_channels.push_back(c);
    }

    std::sort(m_channels.begin(), m_channels.end(),
              [](const Channel &lh, const Channel &rh) {
                  return lh.position() < rh.position();
              });
}
