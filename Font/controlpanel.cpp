#include "controlpanel.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QVBoxLayout>

const char* ControlPanel::X_LABEL = "X";
const char* ControlPanel::Y_LABEL = "Y";
const char* ControlPanel::SCALE_LABEL = "Scale";

ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent)
{
    xControlBlock = new ControlBlock();
    connect(xControlBlock, &ControlBlock::valueChanged, this, &ControlPanel::xChanged);
    xControlBlock->setLabel(X_LABEL);
    xControlBlock->setRange(X_MIN, X_MAX);


    yControlBlock = new ControlBlock();
    connect(yControlBlock, &ControlBlock::valueChanged, this, &ControlPanel::yChanged);
    yControlBlock->setLabel(Y_LABEL);
    yControlBlock->setRange(Y_MIN, Y_MAX);

    scaleControlBlock = new ControlBlock();
    connect(scaleControlBlock, &ControlBlock::valueChanged, this, &ControlPanel::scaleChanged);
    scaleControlBlock->setLabel(SCALE_LABEL);
    scaleControlBlock->setRange(SCALE_MIN, SCALE_MAX);

    auto box = new QGroupBox("Controls");
    auto boxWrapper = new QVBoxLayout();
    box->setStyleSheet("QGroupBox { border: 2px solid gray; border-radius: 4px; }");

    fillCheckbox = new QCheckBox("Filling", this);
    connect(fillCheckbox, &QCheckBox::clicked, this, &ControlPanel::fillChanged);
    outlineCheckbox = new QCheckBox("Outline", this);
    connect(outlineCheckbox, &QCheckBox::clicked, this, &ControlPanel::outlineChanged);

    auto layout = new QGridLayout();
    layout->addWidget(xControlBlock, 0, 0);
    layout->addWidget(yControlBlock, 1, 0);
    layout->addWidget(scaleControlBlock, 2, 0);
    layout->addWidget(fillCheckbox, 3, 0);
    layout->addWidget(outlineCheckbox, 4, 0);

    box->setLayout(layout);
    boxWrapper->addWidget(box);
    setLayout(boxWrapper);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void ControlPanel::setX(int x)
{
    xControlBlock->setValue(x);
}

void ControlPanel::setY(int y)
{
    yControlBlock->setValue(y);
}

void ControlPanel::setScale(int scale)
{
    scaleControlBlock->setValue(scale);
}

void ControlPanel::updateValues(int x, int y, int scale, bool fill, bool outline)
{
    xControlBlock->updateValue(x);
    yControlBlock->updateValue(y);
    scaleControlBlock->updateValue(scale);
    outlineCheckbox->setChecked(outline);
    fillCheckbox->setChecked(fill);
}

int ControlPanel::getX()
{
    return xControlBlock->getValue();
}

int ControlPanel::getScale()
{
    return scaleControlBlock->getValue();
}

bool ControlPanel::getFill()
{
    return fillCheckbox->isChecked();
}

bool ControlPanel::getOutline()
{
    return outlineCheckbox->isChecked();
}

int ControlPanel::getY()
{
    return yControlBlock->getValue();
}
