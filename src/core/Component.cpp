#include "Component.hpp"

#include <QJsonArray>
#include <utility>

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
    Component::unmarshal(std::move(o));
}

void Component::unmarshal(const QJsonObject &&o)
{
    if (o[QStringLiteral("type")] == 1) {
        Action_Row a;
        if (o.contains(QStringLiteral("components"))) {
            a.buttons()->reserve(
                o[QStringLiteral("componenets")].toArray().size());
            const auto &comp_array{ o[QStringLiteral("components")].toArray() };
            for (const auto &b : comp_array) {
                Button but;
                but.unmarshal(b.toObject());
                a.buttons()->emplace_back(but);
            }
        }
        m_component.emplace<Action_Row>(a);
    } else {
        // Button but;
        // but.unmarshal(o);
        // m_component.emplace<Button>(but);
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
    m_url = o[QStringLiteral("url")].toString();
    if (o.contains(QStringLiteral("style")))
        m_style = static_cast<Button_Style>(o[QStringLiteral("style")].toInt());
    if (o.contains(QStringLiteral("emoji"))) {
        // Emoji t;
        // t.unmarshal(o[QStringLiteral("emoji")].toObject());
        // m_emoji.emplace(t);
    }
    if (o.contains(QStringLiteral("label")))
        m_label = o[QStringLiteral("label")].toString();
    if (o.contains(QStringLiteral("custom_id")))
        m_custom_id = o[QStringLiteral("custom_id")].toString();
    if (o.contains(QStringLiteral("url")))
        m_url = o[QStringLiteral("url")].toString();
    if (o.contains(QStringLiteral("disabled")))
        m_disabled = o[QStringLiteral("disabled")].toBool();
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
/*
optional<Emoji> Button::emoji()
{
    // return m_emoji;
}*/

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
