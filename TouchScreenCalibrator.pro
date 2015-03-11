#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T14:17:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchScreenCalibrator
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Calibration.cpp

HEADERS  += MainWindow.h \
    Calibration.h

FORMS    += MainWindow.ui

RESOURCES += \
    ressources.qrc
