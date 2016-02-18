#include "drawwidget.h"
#include "circle.h"
#include <QPainter>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent) {
    circle = new Circle(this);
}

void DrawWidget::setX(int x) {
    circle->setX(x);
    update();
}

void DrawWidget::setY(int y) {
    circle->setY(y);
    update();
}

void DrawWidget::setR(int r) {
    circle->setR(r);
    update();
}

void DrawWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QImage backBuffer(width(), height(), QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer) {
      return;
    }
    memset(pubBuffer, qRgb(0,0,0), backBuffer.byteCount());
    //
    if (circle) {
      circle->draw(&backBuffer);
    }
    //
    painter.drawImage(0, 0, backBuffer);
}
