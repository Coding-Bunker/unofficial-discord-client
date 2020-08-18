#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include <QJsonObject>
#include <QTime>
#include <QUuid>
#include <optional>

struct Channel {
  public:
    enum class Type {
        GUILD_TEXT = 0,
        DM,
        GUILD_VOICE,
        GROUP_DM,
        GUILD_CATEGORY,
        GUILD_NEWS,
        GUILD_STORE
    };

  public:
    QUuid id;
    Type type;
    QUuid guild_id;
    int position;
    // array of permissions overwrites
    QString name;
    QString topic;
    bool nsfw = false;
    QUuid last_message_id;
    int bitrate;
    unsigned int user_limit;
    unsigned int rate_limit_per_user;
    // reciptions of user objects
    QString icons; // hash
    QUuid owner_id;
    QUuid application_id;
    QUuid parent_id;
    QTime last_pin_timestamp; // converted to ISO8601 standard
};

[[nodiscard]] inline Channel fromJsonToChannel(const QJsonObject &json_ojb);
[[nodiscard]] inline QJsonObject fromChannelToJson(const Channel &channel);

#endif // CHANNEL_HPP
