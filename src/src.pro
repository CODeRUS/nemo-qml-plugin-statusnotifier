TEMPLATE = lib
TARGET = statusnotifier

CONFIG += qt create_pc create_prl no_install_prl c++11
QT += qml dbus gui

CONFIG += c++11

system(qdbusxml2cpp -c StatusNotifierItemInterface -p statusnotifieriteminterface -i dbustypes.h ../dbus/org.kde.StatusNotifierItem.xml)
system(qdbusxml2cpp ../dbus/org.kde.StatusNotifierItem.xml -i statusnotifieritem.h -a statusnotifieritemadaptor)

SOURCES += \
    statusnotifieriteminterface.cpp \
    statusnotifieritemadaptor.cpp \
    dbustypes.cpp \
    sniasync.cpp \
    statusnotifierhost.cpp \
    statusnotifiericon.cpp \
    statusnotifieritem.cpp \
    statusnotifierwatcher.cpp

PUBLIC_HEADERS += \
    dbustypes.h \
    statusnotifierhost.h \
    statusnotifiericon.h \
    statusnotifieritem.h

HEADERS += \
    $$PUBLIC_HEADERS \
    statusnotifieriteminterface.h \
    statusnotifieritemadaptor.h \
    sniasync.h \
    statusnotifierwatcher.h

target.path = $$[QT_INSTALL_LIBS]

develheaders.path = /usr/include/statusnotifier
develheaders.files = $$PUBLIC_HEADERS

pkgconfig.files = $$PWD/pkgconfig/statusnotifier.pc
pkgconfig.path = $$target.path/pkgconfig

QMAKE_PKGCONFIG_NAME = lib$$TARGET
QMAKE_PKGCONFIG_DESCRIPTION = StatusNotifier development files
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$develheaders.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
QMAKE_PKGCONFIG_REQUIRES = Qt5Core Qt5DBus

INSTALLS += target develheaders pkgconfig
