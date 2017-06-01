TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt



LIBS += -lfas
LIBS += -lfashttp
LIBS += -lfasutils
LIBS += -lpthread
LIBS += -lmemcachedutil
LIBS += -lmemcached
LIBS += -ljsoncpp

INCLUDEPATH += "fas/base"
QMAKE_LIBDIR += "/home/fas/workspace/cc/C++/QtWorkplace/mdm/lib"

QMAKE_CXXFLAGS += -std=c++11 --static
QMAKE_LIBDIR += "/usr/local/libmemcached/lib"
INCLUDEPATH += "/usr/local/libmemcached/include"

QMAKE_CXXFLAGS += -std=c++11 -static

SOURCES += mcacheTask.cpp \
    mcacheTaskServer.cpp \
    mcacheTaskHandle.cpp \
    ConsistencyHash.cpp \
    HashNode.cpp \
    Md5.cpp \
    memcachedprotocol.cpp \
    mdm.cpp \
    memcachedProtocol.cpp \
    mdmInfoLoader.cpp

HEADERS += \
    mcacheTask.h \
    mcacheTaskServer.h \
    mcacheTaskHandle.h \
    ConsistencyHash.h \
    HashNode.h \
    Md5.h \
    mdmtypes.h \
    memcachedProtocol.h \
    mdmInfoLoader.h
