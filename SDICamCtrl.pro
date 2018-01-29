#-------------------------------------------------
#
# Project created by QtCreator 2018-01-10T21:38:26
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SDICamCtrl
TEMPLATE = app

CONFIG += console

SOURCES += main.cpp\
        mainwindow.cpp \
    ctrlcmd.cpp \
    ctrlres.cpp \
    serialdata.cpp

HEADERS  += mainwindow.h \
    ctrlcmd.h \
    ctrlres.h \
    serialdata.h

FORMS    += mainwindow.ui
