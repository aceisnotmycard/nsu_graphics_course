#include "consolecontroller.h"
#include "windowcontroller.h"


int main(int argc, char *argv[])
{
    IController* controller;
    if (argc > 1) {
        controller = new ConsoleController();
    } else {
        controller = new WindowController();
    }
    return controller->start(argc, argv);
}
