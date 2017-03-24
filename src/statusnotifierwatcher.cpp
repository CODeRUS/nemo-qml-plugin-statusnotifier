/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXDE-Qt - a lightweight, Qt based, desktop toolset
 * http://lxqt.org
 *
 * Copyright: 2015 LXQt team
 * Authors:
 *  Balázs Béla <balazsbela[at]gmail.com>
 *  Paulo Lieuthier <paulolieuthier@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "statusnotifierwatcher.h"

StatusNotifierWatcher::StatusNotifierWatcher(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<IconPixmap>("IconPixmap");
    qDBusRegisterMetaType<IconPixmap>();
    qRegisterMetaType<IconPixmapList>("IconPixmapList");
    qDBusRegisterMetaType<IconPixmapList>();
    qRegisterMetaType<ToolTip>("ToolTip");
    qDBusRegisterMetaType<ToolTip>();

    QDBusConnection dbus = QDBusConnection::sessionBus();
    if (!dbus.registerService(QStringLiteral("org.kde.StatusNotifierWatcher")))
        qDebug() << QDBusConnection::sessionBus().lastError().message();
    if (!dbus.registerObject(QStringLiteral("/StatusNotifierWatcher"), this, QDBusConnection::ExportScriptableContents))
        qDebug() << QDBusConnection::sessionBus().lastError().message();

    m_watcher = new QDBusServiceWatcher(this);
    m_watcher->setConnection(dbus);
    m_watcher->setWatchMode(QDBusServiceWatcher::WatchForUnregistration);

    connect(m_watcher, &QDBusServiceWatcher::serviceUnregistered, this, &StatusNotifierWatcher::serviceUnregistered);
}

StatusNotifierWatcher::~StatusNotifierWatcher()
{
    QDBusConnection::sessionBus().unregisterService(QStringLiteral("org.kde.StatusNotifierWatcher"));
}

void StatusNotifierWatcher::RegisterStatusNotifierItem(const QString &serviceOrPath)
{
    QString service = serviceOrPath;
    QString path = QStringLiteral("/StatusNotifierItem");

    QString notifierItemId = service + path;

    if (QDBusConnection::sessionBus().interface()->isServiceRegistered(service).value()
        && !m_services.contains(notifierItemId))
    {
        m_services << notifierItemId;
        m_watcher->addWatchedService(service);
        emit StatusNotifierItemRegistered(notifierItemId);
    }
}

void StatusNotifierWatcher::RegisterStatusNotifierHost(const QString &service)
{
    if (!m_hosts.contains(service))
    {
        m_hosts.append(service);
        m_watcher->addWatchedService(service);
    }
}

void StatusNotifierWatcher::serviceUnregistered(const QString &service)
{
    qDebug() << "Service" << service << "unregistered";

    m_watcher->removeWatchedService(service);

    if (m_hosts.contains(service))
    {
        m_hosts.removeAll(service);
        return;
    }

    QString match = service + '/';
    QStringList::Iterator it = m_services.begin();
    while (it != m_services.end())
    {
        if (it->startsWith(match))
        {
            QString name = *it;
            it = m_services.erase(it);
            emit StatusNotifierItemUnregistered(name);
        }
        else
            ++it;
    }
}
