system(qdbusxml2cpp -c StatusNotifierItemInterface -p statusnotifieriteminterface -i dbustypes.h org.kde.StatusNotifierItem.xml)
system(qdbusxml2cpp org.kde.StatusNotifierItem.xml -i statusnotifieritem.h -a statusnotifieritemadaptor)

TARGET = statusnotifier
PLUGIN_IMPORT_PATH = org/nemomobile/statusnotifier
QT += dbus qml
QT -= gui
TEMPLATE = lib
CONFIG += qt plugin hide_symbols c++11
target.path = $$[QT_INSTALL_QML]/$$PLUGIN_IMPORT_PATH
INSTALLS += target
qmldir.files += \
        $$_PRO_FILE_PWD_/qmldir \
        $$_PRO_FILE_PWD_/plugins.qmltypes
qmldir.path +=  $$target.path
INSTALLS += qmldir
SOURCES += \
    plugin.cpp \
    statusnotifieriteminterface.cpp \
    statusnotifieritemadaptor.cpp \
    dbustypes.cpp \
    declarativestatusnotifieritem.cpp \
    sniasync.cpp \
    statusnotifierhost.cpp \
    statusnotifiericon.cpp \
    statusnotifieritem.cpp \
    statusnotifiermodel.cpp \
    statusnotifierwatcher.cpp

HEADERS += \
    plugin.h \
    statusnotifieriteminterface.h \
    statusnotifieritemadaptor.h \
    dbustypes.h \
    declarativestatusnotifieritem.h \
    sniasync.h \
    statusnotifierhost.h \
    statusnotifiericon.h \
    statusnotifieritem.h \
    statusnotifiermodel.h \
    statusnotifierwatcher.h

OTHER_FILES += \
    org.kde.StatusNotifierItem.xml

DISTFILES += \
    plugins.qmltypes \
    rpm/nemo-qml-plugin-statusnotifier.spec
