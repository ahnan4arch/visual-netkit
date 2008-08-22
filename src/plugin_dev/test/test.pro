# #####################################################################
# Automatically generated by qmake (2.01a) lun mag 19 18:38:13 2008
# #####################################################################
TEMPLATE = lib
TARGET = test

#prevent linking error on some system (like ubuntu)
QMAKE_LFLAGS = -Wl,-rpath,$$[QT_INSTALL_LIBS] $$[QMAKE_LFLAGS_SHLIB]

DEPENDPATH += .
DESTDIR = ../../../bin/plugins

#QtXml is used by property expert to parse plugin xml config file
QT += xml

VERSION = 1.1

MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
OBJECTS_DIR = build/obj

INCLUDEPATH += . \
    ../../plugin_framework \
    ../../core

RESOURCES = resources/resources.qrc

# Input
HEADERS += PluginTest.h \
    ../../plugin_framework/PluginProxy.h

SOURCES += PluginTest.cpp \
    ../../plugin_framework/PluginProxy.cpp \
    ../../core/VirtualMachine.cpp \
    ../../core/HardwareInterface.cpp \
    ../../core/CollisionDomain.cpp \
    ../../plugin_framework/PluginProperty.cpp \
    ../../plugin_framework/PluginRegistry.cpp \
    ../../plugin_framework/PropertyExpert.cpp
