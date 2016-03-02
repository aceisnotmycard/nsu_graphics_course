#include "circle.h"
#include "mainwindow.h"
#include "windowcontroller.h"

#include <QApplication>

WindowController::WindowController() : IController() {

}

int WindowController::start(int argc, char** argv)
{
    QApplication a(argc, argv);
    sceneController = new SceneController();
    MainWindow mainWindow(sceneController);
    mainWindow.show();
    return a.exec();
}


