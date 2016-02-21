#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include "controlblock.h"

class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QWidget* parent=0);
    void setX(int value);
    void setY(int value);
    void setR(int value);

    int getX();
    int getY();
    int getR();

signals:
    void xChanged(int x);
    void yChanged(int y);
    void rChanged(int r);
private:
    ControlBlock* xBlock;
    ControlBlock* yBlock;
    ControlBlock* rBlock;

    static const int X_MIN = -10000;
    static const int X_MAX = 10000;
    static const int X_START = 0;
    static const char* X_LABEL;
    static const int Y_MIN = -10000;
    static const int Y_MAX = 10000;
    static const int Y_START = 0;
    static const char* Y_LABEL;
    static const int R_MIN = 1;
    static const int R_MAX = 1000;
    static const int R_START = 20;
    static const char* R_LABEL;
};

#endif // CONTROLS_H
