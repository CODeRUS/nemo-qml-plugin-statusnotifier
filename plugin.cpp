#include "plugin.h"

void StatusNotifierPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QStringLiteral("org.nemomobile.statusnotifier"));
    qmlRegisterType<StatusNotifierModel>("org.nemomobile.statusnotifier", 1, 0, "StatusNotifierModel");
    qmlRegisterType<DeclarativeStatusNotifierItem>("org.nemomobile.statusnotifier", 1, 0, "StatusNotifierItem");
    qmlRegisterUncreatableType<StatusNotifierIcon>("org.nemomobile.statusnotifier", 1, 0, "StatusNotifierIcon", QStringLiteral("StatusNotifierIcon in uncreatable"));
}
