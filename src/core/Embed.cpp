#include "Embed.hpp"

optional<QString> Embed::title() const
{
    return m_title;
}

optional<QString> Embed::type() const
{
    return m_type;
}

optional<QString> Embed::desc() const
{
    return m_desc;
}

optional<QString> Embed::url() const
{
    return m_url;
}

optional<unsigned long> Embed::color() const
{
    return m_color;
}

optional<QDateTime> Embed::ts() const
{
    return m_ts;
}

optional<QList<Embed_field>> Embed::fields() const
{
    return m_fields;
}

optional<Embed_footer> Embed::foot() const
{
    return m_foot;
}

optional<Embed_MM> Embed::img() const
{
    return m_img;
}

optional<Embed_MM> Embed::thumbnail() const
{
    return m_thumbnail;
}

optional<Embed_MM> Embed::video() const
{
    return m_video;
}

optional<Embed_MM> Embed::provider() const
{
    return m_provider;
}

optional<Embed_MM> Embed::author() const
{
    return m_author;
}
