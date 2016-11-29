#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T14:23:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

## ---------------------------
# http://stackoverflow.com/questions/24243176/how-to-specify-target-mac-os-x-version-using-qmake
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12

macx {
    -mmacosx-version-min=10.12
}

## ---------------------------


TARGET = MyTestPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h

FORMS    += mainwindow.ui
