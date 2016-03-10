#include "config.h"

#include <QFile>
#include <QJsonObject>
#include <QDebug>

namespace Config {

QMap<QString, int>* Config::load(const QString& fileName) {
    auto settings = new QMap<QString, int>();

    QFile saveFile(fileName);
    saveFile.open(QFile::ReadOnly | QFile::Text);
    QJsonDocument jsonSave(QJsonDocument::fromJson(saveFile.readAll()));
    QJsonObject saveObject = jsonSave.object();


    (*settings)["x1"] = saveObject["lemniscate"].toObject()["focus1"].toObject()["x"].toInt();
    (*settings)["y1"] = saveObject["lemniscate"].toObject()["focus1"].toObject()["y"].toInt();
    (*settings)["x2"] = saveObject["lemniscate"].toObject()["focus2"].toObject()["x"].toInt();
    (*settings)["y2"] = saveObject["lemniscate"].toObject()["focus2"].toObject()["y"].toInt();
    (*settings)["width"] = saveObject["panel"].toObject()["size"].toObject()["width"].toInt();
    (*settings)["height"] = saveObject["panel"].toObject()["size"].toObject()["height"].toInt();
    return settings;
}

}
