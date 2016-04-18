#include "canvas.h"
#include "drawable.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>

#include <QDebug>

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    drawables = new std::vector<std::shared_ptr<IDrawable>>();
}

void Canvas::addDrawable(std::shared_ptr<IDrawable> drawable)
{
    drawables->push_back(drawable);
}

void Canvas::setController(IController* controller) {
    this->controller = controller;
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
        it->draw(&backBuffer, qRgb(0,0,0));
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        start_pos = event->pos();
    }
}

void Canvas::wheelEvent(QWheelEvent *event) {
    emit scaleChanged(controller->getScale() + event->delta());
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton)) {
            return;
    }
    QPoint p = event->pos() - start_pos;
    if (p.manhattanLength() < QApplication::startDragDistance()) {
            return;
    }
    emit xChanged(controller->getX() + p.x());
    emit yChanged(controller->getY() - p.y());
    start_pos = event->pos();
}

void Canvas::capture(const QString& filename, int width, int height, const std::vector<std::shared_ptr<IDrawable>>& drawables) {
    QImage backBuffer(width, height, QImage::Format_RGB888);
    draw(backBuffer, drawables);
    backBuffer.save(filename, "png");
}

