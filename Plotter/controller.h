#ifndef CONTROLLER_H
#define CONTROLLER_H

class IController {
public:
    IController() {}
    virtual int start(int argc, char** argv) = 0;
};

#endif // CONTROLLER_H
