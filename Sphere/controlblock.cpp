#include "controlblock.h"

#include <QGridLayout>
#include <functional>

ControlBlock::ControlBlock(QWidget *parent) : QWidget(parent)
{
    auto gridLayout = new QGridLayout();
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox();
    label = new QLabel();

    gridLayout->addWidget(label, 0, 1);
    gridLayout->addWidget(spinBox, 0, 2);
    gridLayout->addWidget(slider, 1, 1, 1, 2);
    setLayout(gridLayout);

    connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    //connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
}

void ControlBlock::setLabel(const QString& text)
{
    label->setText(text);
}

void ControlBlock::setRange(int min, int max)
{
    slider->setRange(min, max);
    spinBox->setRange(min, max);
}

void ControlBlock::updateValue(int value) {
    slider->setValue(value);
}

void ControlBlock::setValue(int value)
{
    slider->setValue(value);
    emit valueChanged(value);
}

int ControlBlock::getValue()
{
    return slider->value();
}
