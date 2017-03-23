#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtGlobal>

#include <QtQml>
#include <QQmlExtensionPlugin>

#include "declarativestatusnotifieritem.h"
#include "statusnotifiermodel.h"

class Q_DECL_EXPORT StatusNotifierPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.nemomobile.statusnotifier")
public:
    void registerTypes(const char *uri);
};

#endif // PLUGIN_H
