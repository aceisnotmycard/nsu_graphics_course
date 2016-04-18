#include "config.h"

#include <QFile>
#include <QJsonObject>
#include <QDebug>

namespace Config {

QJsonObject Config::load(const QString& fileName) {
    QFile saveFile(fileName);
    saveFile.open(QFile::ReadOnly | QFile::Text);
    QJsonDocument jsonSave(QJsonDocument::fromJson(saveFile.readAll()));
    qDebug() << jsonSave.isEmpty();
    return jsonSave.object();
}

//TODO: add own serialization method to each drawable
QJsonDocument* save(int x1, int y1, int x2, int y2, int height, int width)
{
    QJsonObject focus1;
    focus1["x"] = x1;
    focus1["y"] = y1;

    QJsonObject focus2;
    focus2["x"] = x2;
    focus2["y"] = y2;

    QJsonObject lemniscate;
    lemniscate["focus1"] = focus1;
    lemniscate["focus2"] = focus2;

    QJsonObject panel;
    QJsonObject size;
    size["width"] = width;
    size["height"] = height;
    panel["size"] = size;

    QJsonObject outer;
    outer["lemniscate"] = lemniscate;
    outer["panel"] = panel;

    return new QJsonDocument(outer);
}

}
