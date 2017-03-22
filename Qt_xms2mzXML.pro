#-------------------------------------------------
#
# Project created by QtCreator 2016-06-13T09:50:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_xms2mzXML
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

QMAKE_LFLAGS_WINDOWS = /SUBSYSTEM:WINDOWS,5.01
