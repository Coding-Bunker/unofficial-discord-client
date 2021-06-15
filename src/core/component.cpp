#include "Component.hpp"

#include <QJsonArray>

constexpr int Component::type()
{
    // XXX: kludge here
    if (m_component.index() == 0)
        // Action row
        return 1;
    else
        // Button
        return 2;
}

void Component::unmarshal(const QJsonObject &o)
{
    if (o["type"] == 1) {
        Action_Row a;
        if (o.contains("components")) {
            for (const auto &b : o["components"].toArray()) {
                const auto &l{ b.toObject() };
            }
        }
    } else {
    }
}

/*
template<class T> constexpr T &get(Component &c)
{
    int k = c.index();
    return std::get<k>(c);
}
*/

void Button::unmarshal(const QJsonObject &o)
{
    Button::unmarshal(std::move(o));
}

void Button::unmarshal(const QJsonObject &&o)
{
    m_url = o["url"].toString();
    if (o.contains("style"))
        m_style = static_cast<Button_Style>(o["style"].toInt());
    if (o.contains("emoji")) {
        Emoji t;
        t.unmarshal(o["emoji"].toObject());
        m_emoji.emplace(t);
    }
    if (o.contains("label"))
        m_label = o["label"].toString();
    if (o.contains("custom_id"))
        m_custom_id = o["custom_id"].toString();
    if (o.contains("url"))
        m_url = o["url"].toString();
    if (o.contains("disabled"))
        m_disabled = o["disabled"].toBool();
}

int Button::getType() const
{
    return type;
}

Button_Style Button::style() const
{
    return m_style;
}

optional<QString> Button::label() const
{
    return m_label;
}

optional<QString> Button::custom_id() const
{
    return m_custom_id;
}

optional<bool> Button::disabled() const
{
    return m_disabled;
}

/* TODO: the emoji class has a member containing a user object, which is a
 * subclass of QObject. Error occurs because QObject is not copyable, and it
 * somehow propogates down through inheritance to where the emoji member getter
 * does not work at the moment.
 */

optional<Emoji> Button::emoji()
{
    // return m_emoji;
}

optional<QString> Button::url() const
{
    return m_url;
}

int Action_Row::getType() const
{
    return type;
}

optional<QList<Button>> Action_Row::buttons() const
{
    return m_buttons;
}
