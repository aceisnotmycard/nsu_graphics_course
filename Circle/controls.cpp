#include "controls.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <functional>

const char* Controls::X_LABEL = "Pos X";
const char* Controls::Y_LABEL = "Pos Y";
const char* Controls::R_LABEL = "Radius";

Controls::Controls(QWidget* parent) : QWidget(parent)
{
    xBlock = new ControlBlock(this);
    yBlock = new ControlBlock(this);
    rBlock = new ControlBlock(this);

    connect(xBlock, &ControlBlock::valueChanged, this, &Controls::xChanged);
    connect(yBlock, &ControlBlock::valueChanged, this, &Controls::yChanged);
    connect(rBlock, &ControlBlock::valueChanged, this, &Controls::rChanged);

    xBlock->setRange(X_MIN, X_MAX);
    xBlock->setValue(X_START);
    xBlock->setLabel(X_LABEL);

    yBlock->setRange(Y_MIN, Y_MAX);
    yBlock->setValue(Y_START);
    yBlock->setLabel(Y_LABEL);

    rBlock->setRange(R_MIN, R_MAX);
    rBlock->setValue(R_START);
    rBlock->setLabel(R_LABEL);

    auto box = new QGroupBox("Controls");
    auto boxWrapper = new QVBoxLayout();
    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");

    auto layout = new QGridLayout();
    layout->addWidget(xBlock, 0, 0);
    layout->addWidget(yBlock, 1, 0);
    layout->addWidget(rBlock, 2, 0);

    box->setLayout(layout);
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void Controls::setX(int value)
{
    xBlock->setValue(value);
}

void Controls::setY(int value)
{
    yBlock->setValue(value);
}

void Controls::setR(int value)
{
    rBlock->setValue(value);
}

int Controls::getX()
{
    return xBlock->getValue();
}

int Controls::getY()
{
    return yBlock->getValue();
}

int Controls::getR()
{
    return rBlock->getValue();
}
