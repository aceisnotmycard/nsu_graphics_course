#include "mainwindow.h"
#include "scenecontroller.h"

#include <QVBoxLayout>

MainWindow::MainWindow(SceneController* sceneController, int width, int height, QWidget *parent) : QMainWindow(parent)
{
    auto hBoxLayout = new QHBoxLayout();
    auto centralWidget = new QWidget(this);
    drawWidget = new DrawWidget(this);
    sceneController->setCanvas(drawWidget->getCanvas());
    controlPanel = new ControlPanel(this);
    hBoxLayout->addWidget(drawWidget);
    hBoxLayout->addWidget(controlPanel, 0, Qt::AlignTop);

    connect(controlPanel, &ControlPanel::x1Changed, sceneController, &SceneController::updateX1);
    connect(controlPanel, &ControlPanel::x2Changed, sceneController, &SceneController::updateX2);
    connect(controlPanel, &ControlPanel::y1Changed, sceneController, &SceneController::updateY1);
    connect(controlPanel, &ControlPanel::y2Changed, sceneController, &SceneController::updateY2);

    centralWidget->setLayout(hBoxLayout);
    setCentralWidget(centralWidget);
    resize(width, height);
}
