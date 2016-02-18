#-------------------------------------------------
#
# Project created by QtCreator 2016-02-16T17:54:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Circle
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    drawwidget.cpp \
    circle.cpp \
    controlblock.cpp \
    controls.cpp

HEADERS  += mainwindow.h \
    drawwidget.h \
    circle.h \
    controlblock.h \
    controls.h

FORMS    += mainwindow.ui

CONFIG += c++11
