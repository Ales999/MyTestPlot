#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T14:23:57
#
#-------------------------------------------------

QT       += core gui

CONFIG	+= qt
CONFIG	+= c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

## ---------------------------
# http://stackoverflow.com/questions/24243176/how-to-specify-target-mac-os-x-version-using-qmake
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12

macx {
    -mmacosx-version-min=10.12
}

## -------- Homebrew Ta-Lib  ----------------
#mac{
#INCLUDEPATH += /usr/local/Cellar/ta-lib/0.4.0/include
#LIBS += -L/usr/local/Cellar/ta-lib//0.4.0/lib
#LIBS += -lta_lib
#}

## ---------------------------------


## ---------------------------------

mac{
#LIBS+= -dead_strip
QMAKE_MAC_SDK = macosx10.12

#LIBS += -framework CoreFoundation
#LIBS += -framework ApplicationServices
}

## ---------------------------------

TARGET = MyTestPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        qcustomplot.cpp \
    genrandom.cpp \
    testplotmodel.cpp \
    testplotpresenter.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h \
    threadedobject.h \
    genrandom.h \
    testplotmodel.h \
    testplotpresenter.h \
    itestplotview.h

FORMS    += mainwindow.ui
