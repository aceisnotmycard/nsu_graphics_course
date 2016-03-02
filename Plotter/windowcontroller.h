#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include "controller.h"
#include "drawable.h"
#include "scenecontroller.h"


class WindowController : public IController
{
public:
    WindowController();
    virtual int start(int argc, char** argv);
private:
    SceneController* sceneController;
};

#endif // WINDOWCONTROLLER_H
