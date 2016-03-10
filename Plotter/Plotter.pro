QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Plotter
TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

SOURCES += main.cpp \
    consolecontroller.cpp \
    windowcontroller.cpp \
    controlblock.cpp \
    mainwindow.cpp \
    controlpanel.cpp \
    drawwidget.cpp \
    canvas.cpp \
    circle.cpp \
    scenecontroller.cpp \
    lemniscate.cpp \
    point.cpp \
    axis.cpp

HEADERS += \
    controller.h \
    consolecontroller.h \
    windowcontroller.h \
    controlblock.h \
    mainwindow.h \
    controlpanel.h \
    drawwidget.h \
    canvas.h \
    drawable.h \
    circle.h \
    scenecontroller.h \
    lemniscate.h \
    point.h \
    axis.h
