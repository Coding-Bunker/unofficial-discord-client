#pragma once

#include <QDateTime>
#include <QJsonObject>
#include <optional>

using std::optional;

struct Embed_urls {
    optional<QString> &icon_url, proxy_icon_url;
};

struct Embed_footer : Embed_urls {
    QString &txt;
};

struct Embed_MM : Embed_urls {
    optional<unsigned> &h, w;
};

struct Embed_author : Embed_urls {
    optional<QString> &icon_url, name;
};

struct Embed_provider {
    optional<QString> &name, url;
};

struct Embed_field {
    QHash<QString, QString> &s;
    optional<bool> &m_inline;
};

class Embed
{
  public:
    Embed();

    optional<QString> title() const;
    optional<QString> type() const;
    optional<QString> desc() const;
    optional<QString> url() const;
    optional<unsigned long> color() const;
    optional<QDateTime> ts() const;
    optional<QList<Embed_field>> fields() const;
    optional<Embed_footer> foot() const;
    optional<Embed_MM> img() const;
    optional<Embed_MM> thumbnail() const;
    optional<Embed_MM> video() const;
    optional<Embed_MM> provider() const;
    optional<Embed_MM> author() const;

  private:
    optional<QString> m_title, m_type, m_desc, m_url;
    optional<unsigned long> m_color;
    optional<QDateTime> m_ts;
    optional<QList<Embed_field>> m_fields;
    optional<Embed_footer> m_foot;
    optional<Embed_MM> m_img, m_thumbnail, m_video, m_provider, m_author;
};
