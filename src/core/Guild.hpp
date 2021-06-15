#pragma once

#include "Channel.hpp"
#include "Role.hpp"

enum class NSFW_level : unsigned char {
    Default,
    Explicit,
    Safe,
    Age_Restricted
};
enum class Veri_level : unsigned char {
    None,
    Verified_Email,
    Five_Minutes,
    Ten_Minutes,
    Verified_PhoneNum
};
enum class Explicit_Filter_level : unsigned char {
    None,
    Without_Roles,
    Everyone
};

class Guild
{
  public:
    void unmarshal(const QJsonObject &obj);

    snowflake id() const noexcept;
    QString name() const noexcept;
    QString iconHash() const noexcept;
    QString bannerHash() const noexcept;
    const QByteArray &icondata() const noexcept;

    void addChannel(Channel &&c);

    void addMessageToChannel(Message &&m);

    void setIconBase64(QByteArray &&data);

    QList<Channel> channels;

    void setBannerhash(const QString &newBannerhash);

    snowflake public_updates_channel_id() const;
    const QString &splashHash() const;
    const QString &preferredlocale() const;
    NSFW_level nsfwlvl() const;

    snowflake mfalvl() const;
    void setMfalvl(snowflake newMfalvl);

    snowflake ownerid() const;
    const QString &desc() const;
    const QString &vanity_url() const;
    Veri_level verilvl() const;
    Explicit_Filter_level explilvl() const;
    bool is_only_mentioned() const;

    const QVariantList &roles() const;

  private:
    // Guranteed members to be returned in guild object
    snowflake m_id, m_public_updates_channel_id, m_mfalvl, m_ownerid;
    QString m_name;
    QString m_iconHash;
    QString m_splashHash;
    QString m_preferredlocale;
    QString m_bannerhash;
    QString m_desc;
    QString m_vanity_url;
    QByteArray m_icondata;
    unsigned m_afktimeout;
    NSFW_level m_nsfwlvl;
    Veri_level m_verilvl;
    Explicit_Filter_level m_explilvl;
    bool only_mentioned;
    QVariantList m_roles;
};
