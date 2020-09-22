#pragma once

#include "Guild.hpp"

#include <QVector>
#include <QtDebug>

class QJsonArray;
class QJsonObject;

class User
{
  public:
    void populate(const QJsonObject &info);
    void setGuilds(const QJsonArray &array);

    const QVector<Guild> &guilds() const noexcept;

    friend QDebug operator<<(QDebug dbg, const User &u);

  private:
    QString m_id;
    QString m_username;
    QString m_avatar;
    QString m_discriminator;
    QVector<Guild> m_guilds;
};
