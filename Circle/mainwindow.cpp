#include "mainwindow.h"
#include "drawwidget.h"

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
    controls = new Controls(this, [&](int x) { this->drawWidget->setX(x); },
                                  [&](int y) { this->drawWidget->setY(y); },
                                  [&](int r) { this->drawWidget->setR(r); });
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

    connect(actionLoad, SIGNAL(triggered(bool)), this, SLOT(openConfig()));
    connect(actionSave, SIGNAL(triggered(bool)), this, SLOT(saveConfig()));
}

void MainWindow::loadConfig(QString fileName, QMap<QString, int>& map) {

    QFile saveFile(fileName);
    saveFile.open(QFile::ReadOnly | QFile::Text);
    QByteArray saveData = saveFile.readAll();
    QJsonDocument jsonSave(QJsonDocument::fromJson(saveData));

    QJsonObject saveObject = jsonSave.object();

    map["width"] = saveObject["panel"].toObject()["size"].toObject()["x"].toInt();
    map["height"] = saveObject["panel"].toObject()["size"].toObject()["y"].toInt();
    map["x"] = saveObject["circles"].toArray()[0].toObject()["position"].toObject()["x"].toInt();
    map["y"] = saveObject["circles"].toArray()[0].toObject()["position"].toObject()["y"].toInt();
    map["r"] = saveObject["circles"].toArray()[0].toObject()["R"].toInt();
}

void MainWindow::openConfig() {
    QString fileName = QFileDialog::getOpenFileName(
        this, tr("Load file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;
     QMap<QString, int> configMap;
    loadConfig(fileName, configMap);
    updateUI(configMap);
}

void MainWindow::saveConfig() {
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Save file"), QDir::currentPath(), tr("All files (*.json)")
    );
    if (fileName.isEmpty()) return;

    QFile saveFile(fileName);
    saveFile.open(QFile::WriteOnly | QFile::Text);

    QJsonObject jsonObject;
    QJsonArray jsonCircles;
    QJsonObject jsonCircle;
    QJsonObject jsonPosition;
    QJsonObject jsonPanel;
    QJsonObject jsonSize;

    jsonPosition["x"] = controls->getX();
    jsonPosition["y"] = controls->getY();
    jsonCircle["R"] = controls->getR();
    jsonCircle["position"] = jsonPosition;
    jsonCircles.append(jsonCircle);

    jsonSize["x"] = drawWidget->height();
    jsonSize["y"] = drawWidget->width();
    jsonPanel["size"] = jsonSize;

    jsonObject["circles"] = jsonCircles;
    jsonObject["panel"] = jsonPanel;

    QJsonDocument jsonDocument(jsonObject);
    saveFile.write(jsonDocument.toJson());
}

MainWindow::~MainWindow() {}

void MainWindow::updateUI(QMap<QString, int>& map) {
    drawWidget->resize(map["width"], map["height"]);
    controls->setX(map["x"]);
    controls->setY(map["y"]);
    controls->setR(map["r"]);
}
