#include "config.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <qfile.h>

namespace Config {
void load(QString fileName, QMap<QString, int>& map) {

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

QJsonDocument* save(int x, int y, int r, int height, int width)
{
    QJsonObject jsonObject;
    QJsonArray jsonCircles;
    QJsonObject jsonCircle;
    QJsonObject jsonPosition;
    QJsonObject jsonPanel;
    QJsonObject jsonSize;

    jsonPosition["x"] = x;
    jsonPosition["y"] = y;
    jsonCircle["R"] = r;
    jsonCircle["position"] = jsonPosition;
    jsonCircles.append(jsonCircle);

    jsonSize["x"] = height;
    jsonSize["y"] = width;
    jsonPanel["size"] = jsonSize;

    jsonObject["circles"] = jsonCircles;
    jsonObject["panel"] = jsonPanel;

    return new QJsonDocument(jsonObject);
}

}
