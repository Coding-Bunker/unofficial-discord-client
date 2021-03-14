#include "ImageRender.hpp"

#include <QPainter>

ImageRender::ImageRender(QQuickItem *parent) : QQuickPaintedItem(parent) {}

void ImageRender::paint(QPainter *painter)
{
    painter->drawImage(0, 0, m_source);
}

QImage ImageRender::source() const noexcept
{
    return m_source;
}

void ImageRender::setSource(QImage img)
{
    if (img.isNull()) {
        return;
    }

    m_source = img.scaled(this->width(), this->height(),
                          Qt::AspectRatioMode::KeepAspectRatio,
                          Qt::TransformationMode::SmoothTransformation);
    this->update();
}
