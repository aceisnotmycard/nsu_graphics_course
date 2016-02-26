#include "mainwindow.h"
#include "config.h"
#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>
#include <QDebug>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        QMap<QString, int> configMap;
        Config::load(QString(argv[1]), configMap);
        Circle circle;
        circle.setX(configMap["x"]);
        circle.setY(configMap["y"]);
        circle.setR(configMap["r"]);
        Canvas::capture(&circle,argv[2], configMap["height"], configMap["width"]);
        return 0;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
