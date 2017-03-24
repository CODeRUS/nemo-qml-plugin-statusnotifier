system(qdbusxml2cpp -c StatusNotifierItemInterface -p statusnotifieriteminterface -i dbustypes.h ../dbus/org.kde.StatusNotifierItem.xml)
system(qdbusxml2cpp ../dbus/org.kde.StatusNotifierItem.xml -i statusnotifieritem.h -a statusnotifieritemadaptor)

TARGET = statusnotifier

QT += dbus qml
QT -= gui

TEMPLATE = lib

CONFIG += qt plugin hide_symbols c++11

target.path = $$[QT_INSTALL_LIBS]
INSTALLS += target

SOURCES += \
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
