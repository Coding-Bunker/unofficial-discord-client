#include "Attachment.hpp"

void Attachment::unmarshall(const QJsonObject &obj)
{
    // clazy:excludeall=qt4-qstring-from-array
    m_id = obj["id"].toString().toULongLong();
    // FIXME: tell Qt to add a convenience function to convert to size_t
    m_filesize = obj["size"].toString().toULongLong();
    m_filename = obj["filename"].toString();
    m_url      = obj["url"].toString();
    m_proxyurl = obj["proxy_url"].toString();
    optional<QString> content_type;
    optional<unsigned> h, w;
    if (!obj["content_type"].isUndefined()) {
        m_content_type = content_type.emplace(obj["content_tyoe"].toString());
    }
    if (!obj["height"].isUndefined() && !obj["width"].isUndefined()) {
        if (obj["height"].isNull() && obj["width"].isNull())
            m_height = m_width = h = w = {};

        else {
            m_height = h = obj["height"].toInteger();
            m_width = w = obj["width"].toInteger();
        }
    }
}

snowflake Attachment::id() const
{
    return m_id;
}

size_t Attachment::filesize() const
{
    return m_filesize;
}

const QString &Attachment::filename() const
{
    return m_filename;
}

const QString &Attachment::url() const
{
    return m_url;
}

const QString &Attachment::proxyurl() const
{
    return m_proxyurl;
}

optional<QString> Attachment::content_type() const
{
    return m_content_type;
}

optional<unsigned> Attachment::height() const
{
    return m_height;
}

optional<unsigned> Attachment::width() const
{
    return m_width;
}
