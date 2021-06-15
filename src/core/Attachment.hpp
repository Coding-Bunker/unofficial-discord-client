#pragma once

#include "Types.hpp"

#include <QJsonObject>
#include <optional>

class Attachment
{
  public:
    void unmarshall(const QJsonObject &obj);
    snowflake id() const;
    size_t filesize() const;
    const QString &filename() const;
    const QString &url() const;
    const QString &proxyurl() const;
    std::optional<QString> content_type() const;
    std::optional<unsigned> height() const;
    std::optional<unsigned> width() const;

  private:
    snowflake m_id;
    size_t m_filesize;
    QString m_filename, m_url, m_proxyurl;
    std::optional<QString> m_content_type;
    // Probably won't bite us in the posterior, will it?
    std::optional<unsigned> m_height, m_width;
};
