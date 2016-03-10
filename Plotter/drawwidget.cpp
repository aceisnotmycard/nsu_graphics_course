#include "drawwidget.h"

#include <QGroupBox>
#include <QVBoxLayout>

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    auto box = new QGroupBox();
    auto layout = new QVBoxLayout();
    auto boxLayout = new QVBoxLayout();
    this->canvas = new Canvas();

    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; padding: 10px} ");
    boxLayout->addWidget(canvas);
    box->setLayout(boxLayout);
    layout->addWidget(box);
    this->setLayout(layout);
}

Canvas* DrawWidget::getCanvas() {
    return canvas;
}
