/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * http://lxqt.org
 *
 * Copyright: 2015 LXQt team
 * Authors:
 *  Palo Kisa <palo.kisa@gmail.com>
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

#include "sniasync.h"

SniAsync::SniAsync(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent/* = 0*/)
    : QObject(parent)
    , m_sni{service, path, connection}
{
    //forward StatusNotifierItem signals
    connect(&m_sni, &org::kde::StatusNotifierItem::NewAttentionIcon, this, &SniAsync::NewAttentionIcon);
    connect(&m_sni, &org::kde::StatusNotifierItem::NewIcon, this, &SniAsync::NewIcon);
    connect(&m_sni, &org::kde::StatusNotifierItem::NewOverlayIcon, this, &SniAsync::NewOverlayIcon);
    connect(&m_sni, &org::kde::StatusNotifierItem::NewStatus, this, &SniAsync::NewStatus);
    connect(&m_sni, &org::kde::StatusNotifierItem::NewTitle, this, &SniAsync::NewTitle);
    connect(&m_sni, &org::kde::StatusNotifierItem::NewToolTip, this, &SniAsync::NewToolTip);
}

QDBusPendingReply<QDBusVariant> SniAsync::asyncPropGet(QString const & property)
{
    QDBusMessage msg = QDBusMessage::createMethodCall(m_sni.service(), m_sni.path(), QStringLiteral("org.freedesktop.DBus.Properties"), QStringLiteral("Get"));
    msg << m_sni.interface() << property;
    return m_sni.connection().asyncCall(msg);
}
