#ifndef CONSOLECONTROLLER_H
#define CONSOLECONTROLLER_H

#include "controller.h"


class ConsoleController : public IController
{
public:
    ConsoleController() : IController() {}
    virtual int start(int argc, char** argv);
};

#endif // CONSOLECONTROLLER_H
