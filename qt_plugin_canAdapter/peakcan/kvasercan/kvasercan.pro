#-------------------------------------------------
#
# Project created by QtCreator 2018-08-03T13:54:07
#
#-------------------------------------------------

QT = core serialbus

TARGET = qtkvasercanbus

DEFINES += KVASERCAN_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        kvasercanbackend.cpp \
    main.cpp \
    witness.cpp

HEADERS += \
        kvasercanbackend.h \
        kvasercan_global.h \ 
    kvasercanbackend_p.h \
    canevt.h \
    canlib.h \
    canstat.h \
    obsolete.h \
    predef.h \
    canstat.h \
    witness.h

win32 {
  INCLUDEPATH += Your path here!
  LIBS        += $$PWD/canlib32.a
}

DISTFILES = plugin.json \
    canlib32.lib
PLUGIN_TYPE = canbus
PLUGIN_EXTENDS = serialbus
PLUGIN_CLASS_NAME = KvaserCanBusPlugin
load(qt_plugin)
