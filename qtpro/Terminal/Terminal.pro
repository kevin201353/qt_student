TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    global.cpp \
    listbuf.cpp \
    log.cpp \
    main.cpp \
    myjson.cpp \
    tcp.cpp \
    process.cpp \
    netconfig.cpp \
    ryanConfig.cpp \
    systeminfo.cpp \
    activemq.cpp

HEADERS += \
    include.h \
    listbuf.h \
    log.h \
    myjson.h \
    tcp.h \
    process.h \
    activemq.h \
    netconfig.h \
    ryanConfig.h \
    systeminfo.h

DISTFILES += \
    Makefile
LIBS += -lpthread /usr/local/lib/libjsoncpp.a -lactivemq-cpp

DEFINES += _DEBUG

INCLUDEPATH += /usr/local/include/activemq-cpp-3.9.3 /usr/local/apr/include/apr-1
