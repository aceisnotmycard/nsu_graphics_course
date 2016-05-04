#include "consolecontroller.h"
#include "windowcontroller.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        qDebug() << "Console mode activated";
        (new ConsoleController())->start(argc, argv);;
    } else {
        (new WindowController())->start(argc, argv);;
    }
    return 0;
}
