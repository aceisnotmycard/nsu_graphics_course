#include "drawwidget.h"
#include "circle.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QJsonArray>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent) {

    circle = new Circle(this);

    auto box = new QGroupBox("Draw Panel");
    auto layout = new QVBoxLayout();
    auto boxLayout = new QVBoxLayout();
    canvas = new Canvas(circle);

    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; padding: 10px} ");
    boxLayout->addWidget(canvas);
    box->setLayout(boxLayout);
    layout->addWidget(box);
    this->setLayout(layout);
}

Canvas* DrawWidget::getCanvas() {
    return canvas;
}

void DrawWidget::setX(int x) {
    circle->setX(x);
    canvas->repaint();
}

void DrawWidget::setY(int y) {
    circle->setY(y);
    canvas->repaint();
}

void DrawWidget::setR(int r) {
    circle->setR(r);
    canvas->repaint();
}
