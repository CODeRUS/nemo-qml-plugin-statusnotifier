TARGET = nemostatusnotifier
PLUGIN_IMPORT_PATH = org/nemomobile/statusnotifier

TEMPLATE = lib
CONFIG += qt plugin c++11 hide_symbols

QT += qml dbus network
QT -= gui

PKGCONFIG += profile usb-moded-qt5 nemomodels-qt5 libsailfishkeyprovider connman-qt5

target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target

qmldir.files += $$_PRO_FILE_PWD_/qmldir \
                $$_PRO_FILE_PWD_/plugins.qmltypes
qmldir.path +=  $$[QT_INSTALL_QML]/$$$$PLUGIN_IMPORT_PATH

INSTALLS += qmldir

SOURCES += \
    plugin.cpp

HEADERS += \
    plugin.h

INCLUDEPATH += ..

LIBS += -L..