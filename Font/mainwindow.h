#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlpanel.h"
#include "drawwidget.h"
#include "scenecontroller.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(SceneController *sceneController, int width, int height, QWidget *parent = 0);

signals:

public slots:
private:
    ControlPanel*   controlPanel;
    DrawWidget*     drawWidget;
    SceneController* controller;
private slots:
    void saveConfig();
    void openConfig();
};

#endif // MAINWINDOW_H
