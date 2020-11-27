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
    qDebug() << "add channel " << c.name();
    // TODO: implement it
}
