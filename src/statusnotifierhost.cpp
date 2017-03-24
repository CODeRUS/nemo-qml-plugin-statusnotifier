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

#include "statusnotifierhost.h"

#include <QDebug>

StatusNotifierHost::StatusNotifierHost(QObject *parent) : QObject(parent)
{
    QString dbusName = QString("org.kde.StatusNotifierHost-%1-%2").arg(QCoreApplication::applicationPid()).arg(1);
    if (!QDBusConnection::sessionBus().registerService(dbusName))
        qDebug() << QDBusConnection::sessionBus().lastError().message();

    m_watcher = new StatusNotifierWatcher;
    m_watcher->RegisterStatusNotifierHost(dbusName);

    connect(m_watcher, &StatusNotifierWatcher::StatusNotifierItemRegistered,
            this, &StatusNotifierHost::onItemAdded);
    connect(m_watcher, &StatusNotifierWatcher::StatusNotifierItemUnregistered,
            this, &StatusNotifierHost::onItemRemoved);

    qDebug() << m_watcher->RegisteredStatusNotifierItems();
}

void StatusNotifierHost::onItemAdded(const QString &serviceAndPath)
{
    int slash = serviceAndPath.indexOf(QLatin1Char('/'));
    QString serv = serviceAndPath.left(slash);
    QString path = serviceAndPath.mid(slash);

    qDebug() << serv << path;
    StatusNotifierIcon *icon = new StatusNotifierIcon(serv, path, this);
    m_services.insert(serviceAndPath, icon);

    emit itemAdded(icon);
}

void StatusNotifierHost::onItemRemoved(const QString &serviceAndPath)
{
    qDebug() << serviceAndPath;

    if (!m_services.contains(serviceAndPath)) {
        return;
    }

    StatusNotifierIcon *icon = m_services.take(serviceAndPath);
    icon->deleteLater();

    emit itemRemoved(icon);
}
