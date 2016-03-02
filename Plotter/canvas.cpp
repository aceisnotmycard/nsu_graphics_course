#include "canvas.h"
#include "drawable.h"

#include <QPainter>
#include <QDebug>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    drawables = new std::vector<std::shared_ptr<IDrawable>>();
}

void Canvas::addDrawable(std::shared_ptr<IDrawable> drawable)
{
    drawables->push_back(drawable);
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);
    memset(backBuffer.bits(), qRgb(255, 255, 255), backBuffer.byteCount());
    std::for_each(drawables->begin(), drawables->end(), [&](std::shared_ptr<IDrawable> it) { it->draw(&backBuffer); });
    painter.drawImage(0, 0, backBuffer);
}
