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
    teacherform.cpp \
    mylable.cpp \
    classmould.cpp \
    teachervm.cpp \
    classnameconfig.cpp \
    terminaltoolframe.cpp \
    terminalconfig.cpp \
    globalclass.cpp \
    netconfig.cpp \
    loadingframe.cpp \
    log.cpp \
    listbuf.cpp \
    myjson.cpp \
    myhttp.cpp \
    interface.cpp \
    mydialog.cpp \
    tcp.cpp \
    ryanConfig.cpp \
    activemq.cpp \
    process.cpp \
    pointoutframe.cpp

HEADERS  += loginwidget.h \
    setform.h \
    teacherform.h \
    mylable.h \
    classmould.h \
    teachervm.h \
    classnameconfig.h \
    terminaltoolframe.h \
    terminalconfig.h \
    netconfig.h \
    loadingframe.h \
    log.h \
    listbuf.h \
    myjson.h \
    myhttp.h \
    interface.h \
    mydialog.h \
    tcp.h \
    ryanConfig.h \
    include.h \
    activemq.h \
    process.h \
    pointoutframe.h

FORMS    += loginwidget.ui \
    setform.ui \
    teacherform.ui \
    terminaltoolframe.ui \
    loadingframe.ui \
    mydialog.ui \
    pointoutframe.ui

LIBS += -lpthread /usr/local/lib/libjsoncpp.a -L /usr/local/ActiveMQ-CPP/lib -lactivemq-cpp

INCLUDEPATH += /usr/local/ActiveMQ-CPP/include/activemq-cpp-3.9.3 /usr/local/apr/include/apr-1

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lcrypto
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lcrypto
#else:unix: LIBS += -L$$PWD/./ -lcrypto

#INCLUDEPATH += $$PWD/.
#DEPENDPATH += $$PWD/.

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lssl
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lssl
#else:unix: LIBS += -L$$PWD/./ -lssl

#INCLUDEPATH += $$PWD/.
#DEPENDPATH += $$PWD/.

RESOURCES += \
    resource.qrc
