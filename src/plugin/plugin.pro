TARGET = nemostatusnotifier
PLUGIN_IMPORT_PATH = org/nemomobile/statusnotifier

TEMPLATE = lib
CONFIG += qt plugin c++11
QT += qml dbus gui

target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target

qmldir.files += $$_PRO_FILE_PWD_/qmldir \
                $$_PRO_FILE_PWD_/plugins.qmltypes
qmldir.path +=  $$[QT_INSTALL_QML]/$$$$PLUGIN_IMPORT_PATH

INSTALLS += qmldir

SOURCES += \
    plugin.cpp \
    declarativestatusnotifieritem.cpp \
    statusnotifiermodel.cpp

HEADERS += \
    plugin.h \
    declarativestatusnotifieritem.h \
    statusnotifiermodel.h

INCLUDEPATH += ..

LIBS += -L.. -lstatusnotifier
