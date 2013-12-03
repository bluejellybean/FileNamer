#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T17:40:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileNamer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    FileExtensions.cpp

HEADERS  += mainwindow.h \
    FileExtensions.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc
