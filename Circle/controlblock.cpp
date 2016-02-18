#include "controlblock.h"

#include <QGridLayout>
#include <functional>

ControlBlock::ControlBlock(QWidget *parent, std::function<void(int)> callback) : QWidget(parent)
{
    this->callback = callback;
    auto gridLayout = new QGridLayout();
    slider = new QSlider(Qt::Horizontal);
    spinBox = new QSpinBox();
    label = new QLabel();

    gridLayout->addWidget(label, 0, 1);
    gridLayout->addWidget(spinBox, 0, 2);
    gridLayout->addWidget(slider, 1, 1, 1, 2);
    setLayout(gridLayout);

    connect(slider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
    connect(spinBox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(upCall(int)));
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

void ControlBlock::setValue(int value)
{
    slider->setValue(value);
    spinBox->setValue(value);
}

void ControlBlock::upCall(int val)
{
    callback(val);
}

int ControlBlock::getValue()
{
    return slider->value();
}


