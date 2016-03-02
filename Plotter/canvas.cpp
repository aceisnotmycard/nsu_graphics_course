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
    qDebug() << drawable->desc();
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);
    memset(backBuffer.bits(), qRgb(0, 0, 0), backBuffer.byteCount());
    std::for_each(drawables->begin(), drawables->end(), [&](std::shared_ptr<IDrawable> it) { it->draw(&backBuffer); });
    qDebug() << "Number of items: " << drawables->size();
    painter.drawImage(0, 0, backBuffer);
}

void Canvas::draw(QImage& backBuffer, std::shared_ptr<IDrawable> drawable)
{
    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer) {
        return;
    }
    if (drawable) {
        drawable->draw(&backBuffer);
    }
}
