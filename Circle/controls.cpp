#include "controls.h"

#include <QVBoxLayout>
#include <functional>

const char* Controls::X_LABEL = "Pos X";
const char* Controls::Y_LABEL = "Pos Y";
const char* Controls::R_LABEL = "Radius";

Controls::Controls(QWidget* parent,
                   std::function<void(int)> xCallback,
                   std::function<void(int)> yCallback,
                   std::function<void(int)> rCallback) : QWidget(parent)
{
    xBlock = new ControlBlock(this, xCallback);
    yBlock = new ControlBlock(this, yCallback);
    rBlock = new ControlBlock(this, rCallback);

    xBlock->setRange(X_MIN, X_MAX);
    xBlock->setValue(X_START);
    xBlock->setLabel(X_LABEL);

    yBlock->setRange(Y_MIN, Y_MAX);
    yBlock->setValue(Y_START);
    yBlock->setLabel(Y_LABEL);

    rBlock->setRange(R_MIN, R_MAX);
    rBlock->setValue(R_START);
    rBlock->setLabel(R_LABEL);

    auto vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(xBlock);
    vBoxLayout->addWidget(yBlock);
    vBoxLayout->addWidget(rBlock);

    setLayout(vBoxLayout);
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
