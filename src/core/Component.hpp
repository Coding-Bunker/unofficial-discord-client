#pragma once

#include "Emoji.hpp"

#include <QJsonObject>
#include <optional>
#include <variant>

using std::optional;

enum class Button_Style : unsigned char {
    Primary = 1,
    Secondary,
    Success,
    Danger,
    Link
};

class Button
{
    int type{ 2 };
    Button_Style m_style;
    optional<QString> m_label, m_custom_id;
    optional<bool> m_disabled;
    // optional<Emoji> m_emoji;
    optional<QString> m_url;

  public:
    void unmarshal(const QJsonObject &o);
    void unmarshal(const QJsonObject &&o);
    int getType() const;
    Button_Style style() const;
    optional<QString> label() const;
    optional<QString> custom_id() const;
    optional<bool> disabled() const;
    // optional<Emoji> emoji();
    optional<QString> url() const;
};

class Action_Row
{
    int type{ 1 };
    optional<QList<Button>> m_buttons;

  public:
    int getType() const;
    optional<QList<Button>> buttons() const;
};

class Component
{
    std::variant<Action_Row, Button> m_component;

  public:
    constexpr int type();
    void unmarshal(const QJsonObject &o);
    void unmarshal(const QJsonObject &&o);
};

// template<class T> constexpr T &get(Component &c);
