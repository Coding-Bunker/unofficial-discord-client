#include "Guild.hpp"

void Guild::setId(const QString &id)
{
    m_id = id;
}

void Guild::setName(const QString &name)
{
    m_name = name;
}

QString Guild::name() const noexcept
{
    return m_name;
}

QDebug operator<<(QDebug dbg, const Guild &g)
{
    dbg.nospace() << g.m_id << g.m_name;
    return dbg.maybeSpace();
}
