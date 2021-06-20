#pragma once

#include "Types.hpp"

#include <QJsonObject>
#include <optional>

using std::optional;

class Attachment
{
  public:
    void unmarshall(const QJsonObject &obj);
    snowflake id() const;
    size_t filesize() const;
    const QString &filename() const;
    const QString &url() const;
    const QString &proxyurl() const;
    optional<QString> content_type() const;
    optional<unsigned> height() const;
    optional<unsigned> width() const;
    Attachment(snowflake i, QString &n, long long s, const QString &u,
               const QString &pu, const optional<QString> &ct,
               optional<unsigned> h, optional<unsigned> w);
    Attachment() = default;

  private:
    snowflake m_id;
    long long m_filesize;
    QString m_filename, m_url, m_proxyurl;
    optional<QString> m_content_type;
    // Probably won't bite us in the posterior, will it?
    optional<unsigned> m_height, m_width;
};
