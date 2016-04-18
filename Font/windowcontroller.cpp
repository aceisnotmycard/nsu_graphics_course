#include "circle.h"
#include "mainwindow.h"
#include "windowcontroller.h"

#include <QApplication>

WindowController::WindowController() {

}

int WindowController::start(int argc, char** argv)
{
    QApplication app { argc, argv };
    sceneController = new SceneController();
    MainWindow mainWindow { sceneController, 1280, 720 };
    mainWindow.show();
    return app.exec();
}


