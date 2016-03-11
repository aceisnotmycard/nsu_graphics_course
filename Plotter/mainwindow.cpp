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
    sceneController->setCanvas(drawWidget->getCanvas());
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

    connect(controlPanel, &ControlPanel::x1Changed, sceneController, &SceneController::updateX1);
    connect(controlPanel, &ControlPanel::x2Changed, sceneController, &SceneController::updateX2);
    connect(controlPanel, &ControlPanel::y1Changed, sceneController, &SceneController::updateY1);
    connect(controlPanel, &ControlPanel::y2Changed, sceneController, &SceneController::updateY2);

    centralWidget->setLayout(hBoxLayout);
    setCentralWidget(centralWidget);
    resize(width, height);
    updateUI();
}

void MainWindow::openConfig() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Load file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;
    auto configMap = Config::load(fileName);
    updateUI(configMap);
}

void MainWindow::saveConfig() {
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;

    QFile saveFile(fileName);
    saveFile.open(QFile::WriteOnly | QFile::Text);

    auto jsonDocument = Config::save(controlPanel->getX1(),
                                     controlPanel->getY1(),
                                     controlPanel->getX2(),
                                     controlPanel->getY2(),
                                     drawWidget->height(),
                                     drawWidget->width());
    saveFile.write(jsonDocument->toJson());
}

void MainWindow::updateUI(const QMap<QString, int>* config) {
    // Default params
    int x1 = -200;
    int x2 = 200;
    int y1 = 0;
    int y2 = 0;
    if (config != nullptr) {
        x1 = (*config)["x1"];
        x2 = (*config)["x2"];
        y1 = (*config)["y1"];
        y2 = (*config)["y2"];
        resize((*config)["width"], (*config)["height"]);
    }
    controlPanel->setX1(x1);
    controlPanel->setX2(x2);
    controlPanel->setY1(y1);
    controlPanel->setY2(y2);
}
