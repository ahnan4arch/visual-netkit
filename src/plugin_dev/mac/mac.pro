# #####################################################################
# Automatically generated by qmake (2.01a) gio mag 22 22:03:32 2008
# #####################################################################
TEMPLATE = lib
TARGET = mac
DEPENDPATH += .

DESTDIR = ../../../bin/plugins
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
OBJECTS_DIR = build/obj

#QT += network

INCLUDEPATH += . \
    ../../plugin_framework \
    ../../core
    
RESOURCES = resources/resources.qrc

# Input
HEADERS += PluginMac.h \
    ../../plugin_framework/PluginProxy.h

SOURCES += PluginMac.cpp \
    ../../plugin_framework/PluginProxy.cpp \
    ../../core/VirtualMachine.cpp \
    ../../core/HardwareInterface.cpp \
    ../../core/CollisionDomain.cpp \
    ../../plugin_framework/PluginProperty.cpp \
    ../../plugin_framework/PluginRegistry.cpp
