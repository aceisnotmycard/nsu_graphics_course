#include "canvas.h"
#include <QPainter>

Canvas::Canvas(Circle* circle)
{
    this->circle = circle;
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer) {
      return;
    }
    memset(pubBuffer, qRgb(0, 0, 0), backBuffer.byteCount());
    if (circle) {
      circle->draw(&backBuffer);
    }
    painter.drawImage(0, 0, backBuffer);
}
