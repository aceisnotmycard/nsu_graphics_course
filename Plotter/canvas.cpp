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
    draw(backBuffer, *drawables);
    painter.drawImage(0, 0, backBuffer);
}

void Canvas::draw(QImage &backBuffer, const std::vector<std::shared_ptr<IDrawable>>& drawables) {
    memset(backBuffer.bits(), qRgb(255, 255, 255), backBuffer.byteCount());
    for(auto it : drawables) {
        it->draw(&backBuffer);
    }
}

void Canvas::capture(const QString& filename, int width, int height, const std::vector<std::shared_ptr<IDrawable>>& drawables) {
    QImage backBuffer(width, height, QImage::Format_RGB888);
    draw(backBuffer, drawables);
    backBuffer.save(filename, "png");
}

