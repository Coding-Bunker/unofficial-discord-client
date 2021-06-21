#pragma once

#include "Guild.hpp"
#include "Types.hpp"

#include <QVector>
#include <QtDebug>
#include <optional>
#include <utility>

using std::optional;

class User : public QObject
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(QString username READ username NOTIFY usernameChanged)
    // clang-format on

  public:
    void populate(const QJsonDocument &doc);

    QString username() const;

    void setGuilds(const QByteArray &data);
    QList<snowflake> guildIDs() const noexcept;
    QList<std::pair<snowflake, QString>> pairsGuildIDandHashImg() noexcept;

    void setChannelsForGuild(const QByteArray &data);
    void setMessagesForChannel(snowflake guildID, const QByteArray &data);

    void setIconBase64(snowflake guildID, QByteArray &&data);

    friend QDebug operator<<(QDebug dbg, const User &u);

    QList<Guild> guilds;

  signals:
    void usernameChanged();
    void messagesUpdated();

  private:
    snowflake m_id;
    QString m_username;
    QString m_avatar;
    QString m_discriminator;

    void addMessageToGuild(snowflake guildID, Message &&m);
};
