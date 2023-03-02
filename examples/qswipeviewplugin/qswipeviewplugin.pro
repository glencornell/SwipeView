QT += widgets designer uiplugin

CONFIG += plugin
TEMPLATE = lib

TARGET = $$qtLibraryTarget($$TARGET)
target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

include($$PWD/../../QSwipeView/QSwipeView.pri)
include($$PWD/../../QPageIndicator/QPageIndicator.pri)

HEADERS += \
    qswipeviewplugin.hpp \
    qpageindicatorplugin.hpp

SOURCES += \
    qswipeviewplugin.cpp \
    qpageindicatorplugin.cpp

resources.files = \
    images/icons8-swipe-64.png \
    images/icons8-dots-loading-64.png
resources.prefix = /

RESOURCES = resources
