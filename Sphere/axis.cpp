#include "axis.h"

Axis::Axis(bool isVertical) : isVertical(isVertical)
{
}

void Axis::draw(QImage *pBackBuffer, QRgb color)
{
    if (!isVertical) {
        memset(pBackBuffer->bits() + (pBackBuffer->height()/2 * pBackBuffer->bytesPerLine()), color, pBackBuffer->width()*sizeof(uchar)*3);
    } else {
        for (int y = 0; y < pBackBuffer->height(); ++y) {
            memset(pBackBuffer->bits() + (y * pBackBuffer->bytesPerLine()) + (pBackBuffer->width() / 2) * sizeof(uchar)*3, color, sizeof(uchar)*3);
        }
    }
}

QString Axis::desc() const
{
    return QString(isVertical ? "Vertical axis" : "Horizontal axis");
}

const bool Axis::VERTICAL = true;
const bool Axis::HORIZONTAL = false;
