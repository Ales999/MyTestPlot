#-------------------------------------------------
#
# Project created by QtCreator 2016-11-27T14:23:57
#
#-------------------------------------------------

lessThan(QT_VERSION, 5.5): {
error("Qt less than 5.5 is no longer supported. In order to compile Qt Bitcoin Trader you need update to Qt 5.5 and C++11");
}

TEMPLATE	= app
LANGUAGE	= C++
DEPENDPATH	+= .
INCLUDEPATH	+= .
INCLUDEPATH += $$[QT_INSTALL_PREFIX]/src/3rdparty/zlib

#CONFIG	+= qt release
CONFIG	+= qt debug
CONFIG	+= c++11

QT      += core gui
QT      += network script printsupport widgets

## ---------------------------
# http://stackoverflow.com/questions/24243176/how-to-specify-target-mac-os-x-version-using-qmake
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12

macx {
    -mmacosx-version-min=10.12
}

## -------- Homebrew Ta-Lib  ----------------
# mac{
# INCLUDEPATH += /usr/local/Cellar/ta-lib/0.4.0/include
# LIBS += -L/usr/local/Cellar/ta-lib//0.4.0/lib
# LIBS += -lta_lib
# подключение компилятором библиотеки math.c (используется в ta_lib).
# LIBS += -lm
# }

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
    testplotpresenter.cpp \
    depthitem.cpp \
    depthmodel.cpp \
    depthmodelpresenter.cpp \
    currencypairitem.cpp \
    exchange.cpp \
    exchange_random.cpp

HEADERS  += mainwindow.h \
         qcustomplot.h \
    threadedobject.h \
    genrandom.h \
    testplotmodel.h \
    testplotpresenter.h \
    itestplotview.h \
    depthitem.h \
    depthmodel.h \
    depthmodelpresenter.h \
    main.h \
    currencypairitem.h \
    currencyinfo.h \
    exchange.h \
    exchange_random.h

FORMS    += mainwindow.ui
