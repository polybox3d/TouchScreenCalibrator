#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T14:17:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchScreenCalibrator
TEMPLATE = app

#-------------- WE ADD GIT VERSION----------------

GIT_VERSION = $$system(git --git-dir $$PWD/../.git --work-tree $$PWD describe --always --tags)
DEFINES += GIT_VERSION=\\\"$$GIT_VERSION\\\"

SOURCES += main.cpp\
        MainWindow.cpp \
    Calibration.cpp

HEADERS  += MainWindow.h \
    Calibration.h

FORMS    += MainWindow.ui

RESOURCES += \
    ressources.qrc
