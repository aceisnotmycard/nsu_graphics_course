#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "controlblock.h"

#include <QCheckBox>
#include <QWidget>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = 0);
    void setX(int x);
    void setY(int y);
    void setScale(int scale);
    void updateValues(int x, int y, int scale, bool fill, bool outline);

    int getY();
    int getX();
    int getScale();
    bool getFill();
    bool getOutline();
signals:
    void xChanged(int x);
    void yChanged(int y);
    void xRotateChanged(int x_rotate);
    void yRotateChanged(int x_rotate);
    void scaleChanged(int scale);
    void filtrationChanged(bool filtration);

public slots:
private:
    ControlBlock* xControlBlock;
    ControlBlock* yControlBlock;
    ControlBlock* scaleControlBlock;
    ControlBlock* xRotateControlBlock;
    ControlBlock* yRotateControlBlock;
    QCheckBox* fillCheckbox;
    QCheckBox* outlineCheckbox;

    static const int    X_MIN = -10000;
    static const int    X_MAX = 10000;
    static const int    X_START = -200;
    static const char*  X_LABEL;

    static const int    Y_MIN = -10000;
    static const int    Y_MAX = 10000;
    static const int    Y_START = 0;
    static const char*  Y_LABEL;

    static const int    SCALE_MIN = -1000;
    static const int    SCALE_MAX = 1000;
    static const int    SCALE_START = 1;
    static const char*  SCALE_LABEL;
};

#endif // CONTROLPANEL_H
