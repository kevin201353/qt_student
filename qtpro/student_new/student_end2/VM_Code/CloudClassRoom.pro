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
    classmould.cpp \
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
    setroomseatdialog.cpp \
    mydialog.cpp \
    message.cpp \
    testnet.cpp \
    waitstu.cpp \
    waitstu2.cpp \
    myqueue.cpp \
    classnameconfig.cpp \
    qthread.cpp \
    loginwidget.cpp \
    setform.cpp \
    waitstudialog.cpp

HEADERS  += loginwidget.h \
    setform.h \
    classmould.h \
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
    setroomseatdialog.h \
    mydialog.h \
    global.h \
    testnet.h \
    waitstu.h \
    waitstu2.h \
    myqueue.h \
    classnameconfig.h \
    qthread.h \
    waitstudialog.h

FORMS    += loginwidget.ui \
    setform.ui \
    loadingframe.ui \
    setroomseatdialog.ui \
    mydialog.ui \
    waitstu.ui \
    waitstu2.ui \
    waitstudialog.ui

LIBS += -lpthread /usr/local/lib/libjsoncpp.a -L /usr/local/ActiveMQ-CPP/lib -lactivemq-cpp


INCLUDEPATH += /usr/local/ActiveMQ-CPP/include/activemq-cpp-3.9.3 /usr/local/apr/include/apr-1

RESOURCES += \
    resource.qrc
