#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T10:46:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = CloudClassRoom
TEMPLATE = app


SOURCES += main.cpp\
        loginwidget.cpp \
    setform.cpp \
    classmould.cpp \
    classnameconfig.cpp \
    netconfig.cpp \
    globalclass.cpp \
    loadingframe.cpp \
    activemq.cpp \
    process.cpp \
    log.cpp \
    listbuf.cpp \
    ryanConfig.cpp \
    myjson.cpp \
    myhttp.cpp \
    interface.cpp \
    setroomseatdialog.cpp

HEADERS  += loginwidget.h \
    setform.h \
    classmould.h \
    classnameconfig.h \
    netconfig.h \
    loadingframe.h \
    include.h \
    activemq.h \
    process.h \
    log.h \
    listbuf.h \
    ryanConfig.h \
    myjson.h \
    myhttp.h \
    interface.h \
    setroomseatdialog.h

FORMS    += loginwidget.ui \
    setform.ui \
    loadingframe.ui \
    setroomseatdialog.ui
LIBS += -lpthread /usr/local/lib/libjsoncpp.a -lactivemq-cpp

INCLUDEPATH += /usr/local/include/activemq-cpp-3.9.3 /usr/local/apr/include/apr-1
