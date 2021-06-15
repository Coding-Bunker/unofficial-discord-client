#include "Attachment.hpp"

void Attachment::unmarshall(const QJsonObject &obj)
{
    // clazy:excludeall=qt4-qstring-from-array
    m_id = obj[QStringLiteral("id")].toString().toULongLong();
    // FIXME: tell Qt to add a convenience function to convert to size_t
    m_filesize = obj[QStringLiteral("size")].toString().toULongLong();
    m_filename = obj[QStringLiteral("filename")].toString();
    m_url      = obj[QStringLiteral("url")].toString();
    m_proxyurl = obj[QStringLiteral("proxy_url")].toString();
    optional<QString> content_type;
    optional<unsigned> h, w;
    if (!obj[QStringLiteral("content_type")].isUndefined()) {
        m_content_type = content_type.emplace(
            obj[QStringLiteral("content_tyoe")].toString());
    }
    if (obj.contains(QStringLiteral("height")) &&
        !obj.contains(QStringLiteral("width"))) {
        if (obj[QStringLiteral("height")].isNull() &&
            obj[QStringLiteral("width")].isNull())
            m_height = m_width = h = w = {};

        else {
            m_height = h = obj[QStringLiteral("height")].toInteger();
            m_width = w = obj[QStringLiteral("width")].toInteger();
        }
    }
}

Attachment::Attachment(snowflake i, QString &n, long long s, const QString &u,
                       const QString &pu, const optional<QString> &ct,
                       optional<unsigned> h, optional<unsigned> w) :
    m_id(i),
    m_filesize(s), m_filename(n), m_url(u), m_proxyurl(pu), m_content_type(ct),
    m_height(h), m_width(w)
{
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
