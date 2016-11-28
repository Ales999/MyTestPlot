#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T14:23:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = MyTestPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    charts/qcustomplot.cpp

HEADERS  += mainwindow.h \
    charts/qcustomplot.h

FORMS    += mainwindow.ui
