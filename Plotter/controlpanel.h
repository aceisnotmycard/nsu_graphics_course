#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "controlblock.h"

#include <QWidget>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = 0);
    void setX1(int x1);
    void setX2(int x2);
    void setY1(int y1);
    void setY2(int y2);

    int getX1();
    int getX2();
    int getY1();
    int getY2();
signals:
    void x1Changed(int x1);
    void x2Changed(int x2);
    void y1Changed(int y1);
    void y2Changed(int y2);

public slots:
private:
    ControlBlock* x1ControlBlock;
    ControlBlock* y1ControlBlock;
    ControlBlock* x2ControlBlock;
    ControlBlock* y2ControlBlock;

    static const int    X1_MIN = -10000;
    static const int    X1_MAX = 10000;
    static const int    X1_START = -200;
    static const char*  X1_LABEL;

    static const int    Y1_MIN = -10000;
    static const int    Y1_MAX = 10000;
    static const int    Y1_START = 0;
    static const char*  Y1_LABEL;

    static const int    X2_MIN = -10000;
    static const int    X2_MAX = 10000;
    static const int    X2_START = 200;
    static const char*  X2_LABEL;

    static const int    Y2_MIN = -10000;
    static const int    Y2_MAX = 10000;
    static const int    Y2_START = 0;
    static const char*  Y2_LABEL;
};

#endif // CONTROLPANEL_H
