#pragma once

#include <QImage>
#include <QQuickPaintedItem>

class ImageRender : public QQuickPaintedItem
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(QImage source READ source WRITE setSource NOTIFY sourceChanged)
    // clang-format on

  public:
    explicit ImageRender(QQuickItem *parent = nullptr);

    void paint(QPainter *painter) override;

    QImage source() const noexcept;
    void setSource(QImage img);

  signals:
    void sourceChanged();

  private:
    QImage m_source;
};
