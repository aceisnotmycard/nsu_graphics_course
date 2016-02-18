#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    if (argc > 1) {
        QCoreApplication a(argc, argv);
        MainWindow w;
        QMap<QString, int> configMap;
        w.loadConfig(QString(argv[1]), configMap);
        Circle circle;
        circle.setX(configMap["x"]);
        circle.setY(configMap["y"]);
        circle.setR(configMap["r"]);
        Canvas canvas(&circle);
        canvas.capture("test", configMap["height"], configMap["width"]);
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
