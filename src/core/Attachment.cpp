#include "Attachment.hpp"

void Attachment::unmarshall(const QJsonObject &obj)
{
    m_id = obj["id"].toString().toULongLong();
    // FIXME: tell Qt to add a convenience function to convert to size_t
    m_filesize = obj["size"].toString().toULongLong();
    m_filename = obj["filename"].toString();
    m_url      = obj["url"].toString();
    m_proxyurl = obj["proxy_url"].toString();
    if (!obj["content_type"].isUndefined()) {
        m_content_type = obj["content_tyoe"].toString();
    }
    if (!obj["height"].isUndefined() && !obj["width"].isUndefined()) {
        if (obj["height"].isNull() && obj["width"].isNull())
            m_height = m_width = {};

        else {
            m_height = obj["height"].toInteger();
            m_width  = obj["width"].toInteger();
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

std::optional<QString> Attachment::content_type() const
{
    return m_content_type;
}

std::optional<unsigned> Attachment::height() const
{
    return m_height;
}

std::optional<unsigned> Attachment::width() const
{
    return m_width;
}
