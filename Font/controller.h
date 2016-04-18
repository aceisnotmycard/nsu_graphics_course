#ifndef CONTROLLER_H
#define CONTROLLER_H

class IController {
public:
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual int getScale() = 0;
};

#endif // CONTROLLER_H
