TEMPLATE = subdirs

src_plugins.subdir = src/plugin
src_plugins.target = sub-plugins
src_plugins.depends = src

OTHER_FILES += \
    dbus/org.kde.StatusNotifierItem.xml \
    rpm/nemo-qml-plugin-statusnotifier.spec

SUBDIRS = src src_plugins
