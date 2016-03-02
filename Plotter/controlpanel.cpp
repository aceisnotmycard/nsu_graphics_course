#include "controlpanel.h"

#include <QGroupBox>
#include <QVBoxLayout>

const char* ControlPanel::X1_LABEL = "X1";
const char* ControlPanel::X2_LABEL = "X2";
const char* ControlPanel::Y1_LABEL = "Y1";
const char* ControlPanel::Y2_LABEL = "Y2";

ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent)
{
    x1ControlBlock = new ControlBlock();
    connect(x1ControlBlock, &ControlBlock::valueChanged, this, &ControlPanel::x1Changed);
    x1ControlBlock->setLabel(X1_LABEL);
    x1ControlBlock->setRange(X1_MIN, X1_MAX);

    x2ControlBlock = new ControlBlock();
    connect(x2ControlBlock, &ControlBlock::valueChanged, this, &ControlPanel::x2Changed);
    x2ControlBlock->setLabel(X2_LABEL);
    x2ControlBlock->setRange(X2_MIN, X2_MAX);

    y1ControlBlock = new ControlBlock();
    connect(y1ControlBlock, &ControlBlock::valueChanged, this, &ControlPanel::y1Changed);
    y1ControlBlock->setLabel(Y1_LABEL);
    y1ControlBlock->setRange(Y1_MIN, Y1_MAX);

    y2ControlBlock = new ControlBlock();
    connect(y2ControlBlock, &ControlBlock::valueChanged, this, &ControlPanel::y2Changed);
    y2ControlBlock->setLabel(Y2_LABEL);
    y2ControlBlock->setRange(Y2_MIN, Y2_MAX);

    auto box = new QGroupBox("Controls");
    auto boxWrapper = new QVBoxLayout();
    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");

    auto layout = new QGridLayout();
    layout->addWidget(x1ControlBlock, 0, 0);
    layout->addWidget(y1ControlBlock, 1, 0);
    layout->addWidget(x2ControlBlock, 2, 0);
    layout->addWidget(y2ControlBlock, 3, 0);

    box->setLayout(layout);
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}
