#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QByteArray>

void capture(Circle* circle, QString filename, int height, int width)
{
    QImage backBuffer(width, height, QImage::Format_RGB888);

    uchar* pubBuffer = backBuffer.bits();
    if (!pubBuffer) {
      return;
    }
    memset(pubBuffer, qRgb(0, 0, 0), backBuffer.byteCount());
    if (circle) {
      circle->draw(&backBuffer);
    }
    backBuffer.save(filename, "png");
}

void loadConfig(QString fileName, QMap<QString, int>& map) {

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

int main(int argc, char *argv[])
{
    if (argc > 1) {
        QCoreApplication a(argc, argv);
        QMap<QString, int> configMap;
        loadConfig(QString(argv[1]), configMap);
        Circle circle;
        circle.setX(configMap["x"]);
        circle.setY(configMap["y"]);
        circle.setR(configMap["r"]);
        capture(&circle, "test", configMap["height"], configMap["width"]);
        return a.exec();
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
