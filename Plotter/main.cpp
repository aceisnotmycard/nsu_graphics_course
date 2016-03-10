#include "consolecontroller.h"
#include "windowcontroller.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    IController* controller;
    if (argc > 1) {
        qDebug() << "Console mode activated";
        controller = new ConsoleController();
    } else {
        controller = new WindowController();
    }
    return controller->start(argc, argv);
}
