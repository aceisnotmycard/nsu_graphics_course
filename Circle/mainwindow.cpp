#include "mainwindow.h"
#include "drawwidget.h"
#include "config.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <qboxlayout.h>

#include <QAction>
#include <QDebug>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    auto hBoxLayout = new QHBoxLayout();
    auto centralWidget = new QWidget(this);
    drawWidget = new DrawWidget(this);
    controls = new Controls(this);
    hBoxLayout->addWidget(drawWidget);
    hBoxLayout->addWidget(controls, 0, Qt::AlignTop);

    centralWidget->setLayout(hBoxLayout);
    setCentralWidget(centralWidget);
    resize(800, 480);

    auto menu = menuBar()->addMenu(tr("File"));
    auto actionLoad = new QAction(tr("Load"), this);
    auto actionSave = new QAction(tr("Save"), this);
    menu->addAction(actionSave);
    menu->addAction(actionLoad);

    connect(actionLoad, &QAction::triggered, this, &MainWindow::openConfig);
    connect(actionSave, &QAction::triggered, this, &MainWindow::saveConfig);

    connect(controls, &Controls::xChanged, drawWidget, &DrawWidget::setX);
    connect(controls, &Controls::yChanged, drawWidget, &DrawWidget::setY);
    connect(controls, &Controls::rChanged, drawWidget, &DrawWidget::setR);
}


void MainWindow::openConfig() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Load file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;
     QMap<QString, int> configMap;
    Config::load(fileName, configMap);
    updateUI(configMap);
}

void MainWindow::saveConfig() {
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;

    QFile saveFile(fileName);
    saveFile.open(QFile::WriteOnly | QFile::Text);

    auto jsonDocument = Config::save(controls->getX(),
                                     controls->getY(),
                                     controls->getR(),
                                     drawWidget->height(),
                                     drawWidget->width());
    saveFile.write(jsonDocument->toJson());
}

MainWindow::~MainWindow() {}

void MainWindow::updateUI(QMap<QString, int>& map) {
    drawWidget->resize(map["width"], map["height"]);
    controls->setX(map["x"]);
    controls->setY(map["y"]);
    controls->setR(map["r"]);
}
