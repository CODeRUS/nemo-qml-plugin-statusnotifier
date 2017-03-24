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

#ifndef STATUSNOTIFIERHOST_H
#define STATUSNOTIFIERHOST_H

#include <QObject>
#include <QCoreApplication>

#include "statusnotifiericon.h"
#include "statusnotifierwatcher.h"

class StatusNotifierHost : public QObject
{
    Q_OBJECT
public:
    explicit StatusNotifierHost(QObject *parent = 0);

private slots:
    void onItemAdded(const QString &serviceAndPath);
    void onItemRemoved(const QString &serviceAndPath);

signals:
    void itemAdded(StatusNotifierIcon* item);
    void itemRemoved(StatusNotifierIcon* item);

private:
    StatusNotifierWatcher *m_watcher;

    QHash<QString, StatusNotifierIcon*> m_services;
};

#endif // STATUSNOTIFIERHOST_H
