TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "fas/base"

QMAKE_LIBDIR += "/home/fas/workspace/cc/C++/QtWorkplace/mdm/lib"

LIBS += -lfas
LIBS += -lfashttp
LIBS += -lfasutils
LIBS += -lpthread

QMAKE_CXXFLAGS += -std=c++11 -static



SOURCES += main.cpp \
    mcacheTask.cpp \
    mcacheTaskServer.cpp \
    mcacheTaskHandle.cpp

HEADERS += \
    mcacheTask.h \
    mcacheTaskServer.h \
    mcacheTaskHandle.h
