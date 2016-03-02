#include "canvas.h"
#include <QPainter>

Canvas::Canvas(Circle* circle)
{
    this->circle = circle;
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);
    draw(backBuffer, circle);
    painter.drawImage(0, 0, backBuffer);
}

void Canvas::capture(Circle* circle, QString filename, int height, int width)
{
    QImage backBuffer(width, height, QImage::Format_RGB888);
    draw(backBuffer, circle);
    backBuffer.save(filename, "png");
}

void Canvas::draw(QImage& backBuffer, Circle* circle)
{
    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer) {
        return;
    }
    memset(pubBuffer, qRgb(0, 0, 0), backBuffer.byteCount());
    if (circle) {
        circle->draw(&backBuffer);
    }
}
