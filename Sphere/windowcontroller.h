#ifndef WINDOWCONTROLLER_H
#define WINDOWCONTROLLER_H

#include "drawable.h"
#include "scenecontroller.h"


class WindowController
{
public:
    WindowController();
    int start(int argc, char** argv);
private:
    SceneController* sceneController;
};

#endif // WINDOWCONTROLLER_H
