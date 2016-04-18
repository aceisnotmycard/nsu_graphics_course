#include "mainwindow.h"
#include "scenecontroller.h"
#include "config.h"

#include <QAction>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDir>

MainWindow::MainWindow(SceneController* sceneController, int width, int height, QWidget *parent) : QMainWindow(parent)
{
    auto hBoxLayout = new QHBoxLayout();
    auto centralWidget = new QWidget(this);
    drawWidget = new DrawWidget(this);
    controller = sceneController;
    controller->setCanvas(drawWidget->getCanvas());
    controlPanel = new ControlPanel(this);
    hBoxLayout->addWidget(drawWidget);
    hBoxLayout->addWidget(controlPanel, 0, Qt::AlignTop);

    auto menu = menuBar()->addMenu(tr("File"));
    auto actionLoad = new QAction(tr("Load"), this);
    auto actionSave = new QAction(tr("Save"), this);
    menu->addAction(actionSave);
    menu->addAction(actionLoad);

    connect(actionLoad, &QAction::triggered, this, &MainWindow::openConfig);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveConfig);

    connect(controlPanel, &ControlPanel::xChanged, controller, &SceneController::setX);
    connect(controlPanel, &ControlPanel::yChanged, controller, &SceneController::setY);
    connect(controlPanel, &ControlPanel::scaleChanged, controller, &SceneController::setScale);
    connect(controlPanel, &ControlPanel::fillChanged, controller, &SceneController::setFill);
    connect(controlPanel, &ControlPanel::outlineChanged, controller, &SceneController::setOutline);

    connect(controller, &SceneController::fontUpdated, controlPanel, &ControlPanel::updateValues);

    connect(drawWidget->getCanvas(), &Canvas::xChanged, controlPanel, &ControlPanel::setX);
    connect(drawWidget->getCanvas(), &Canvas::yChanged, controlPanel, &ControlPanel::setY);
    connect(drawWidget->getCanvas(), &Canvas::scaleChanged, controlPanel, &ControlPanel::setScale);

    centralWidget->setLayout(hBoxLayout);
    setCentralWidget(centralWidget);
    resize(width, height);
    //updateUI();
}

void MainWindow::openConfig() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Load file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;
    controller->fromJSON(Config::load(fileName));
}

void MainWindow::saveConfig() {
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;

    QFile saveFile(fileName);
    saveFile.open(QFile::WriteOnly | QFile::Text);

//    auto jsonDocument = Config::save(controlPanel->getX1(),
//                                     controlPanel->getY1(),
//                                     controlPanel->getX2(),
//                                     controlPanel->getY2(),
//                                     drawWidget->height(),
//                                     drawWidget->width());
//    saveFile.write(jsonDocument->toJson());
}
