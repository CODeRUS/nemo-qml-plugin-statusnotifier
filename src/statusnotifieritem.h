/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * LXQt - a lightweight, Qt based, desktop toolset
 * http://lxqt.org/
 *
 * Copyright: 2015 LXQt team
 * Authors:
 *   Paulo Lieuthier <paulolieuthier@gmail.com>
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


#ifndef STATUS_NOTIFIER_ITEM_H
#define STATUS_NOTIFIER_ITEM_H

#include <QObject>
#include <QPoint>
#include <QDBusConnection>
#include <QPixmap>
#include <QImage>

#include "dbustypes.h"

class StatusNotifierItemAdaptor;
class DBusMenuExporter;

class StatusNotifierItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Title READ title)
    Q_PROPERTY(QString Status READ status)

    Q_PROPERTY(QString IconName READ iconName)
    Q_PROPERTY(QString OverlayIconName READ overlayIconName)
    Q_PROPERTY(QString AttentionIconName READ attentionIconName)

    Q_PROPERTY(IconPixmapList IconPixmap READ iconPixmap)
    Q_PROPERTY(IconPixmapList OverlayIconPixmap READ overlayIconPixmap)
    Q_PROPERTY(IconPixmapList AttentionIconPixmap READ attentionIconPixmap)

    Q_PROPERTY(ToolTip ToolTip READ toolTip)


public:
    StatusNotifierItem(const QString &category, bool itemIsMenu, const QString &menuPath, QObject *parent = nullptr);
    ~StatusNotifierItem();

    QString title() const;
    void setTitle(const QString &title);

    QString status() const;
    void setStatus(const QString &status);

    QString iconName() const;
    void setIconByName(const QString &name);

    IconPixmapList iconPixmap() const;
    void setIconByPixmap(const QPixmap &icon);
    void setIconByImage(const QImage &icon);

    QString overlayIconName() const;
    void setOverlayIconByName(const QString &name);

    IconPixmapList overlayIconPixmap() const;
    void setOverlayIconByPixmap(const QPixmap &icon);
    void setOverlayIconByImage(const QImage &icon);

    QString attentionIconName() const;
    void setAttentionIconByName(const QString &name);

    IconPixmapList attentionIconPixmap() const;
    void setAttentionIconByPixmap(const QPixmap &icon);
    void setAttentionIconByImage(const QImage &icon);

    ToolTip toolTip() const;

public slots:
    void Activate(int x, int y);
    void SecondaryActivate(int x, int y);
    void ContextMenu(int, int);
    void Scroll(int delta, const QString &orientation);

private:
    void registerToHost();

private slots:
    void onServiceOwnerChanged(const QString &, const QString &,
                               const QString &newOwner);

signals:
    void activateRequested(const QPoint &pos);
    void secondaryActivateRequested(const QPoint &pos);
    void scrollRequested(int delta, Qt::Orientation orientation);

private:
    StatusNotifierItemAdaptor *m_adaptor;

    QString m_service;
    QString m_title;
    QString m_status;

    QString m_iconName, m_overlayIconName, m_attentionIconName;
    IconPixmapList m_icon, m_overlayIcon, m_attentionIcon;

    QDBusConnection m_sessionBus;
};

#endif
