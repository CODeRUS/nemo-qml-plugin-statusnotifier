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

#include "dbustypes.h"

class StatusNotifierItemAdaptor;
class DBusMenuExporter;

class StatusNotifierItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString Title READ title)
    Q_PROPERTY(QString Id READ id)
    Q_PROPERTY(QString Status READ status)

    Q_PROPERTY(QString IconName READ iconName)
    Q_PROPERTY(QString OverlayIconName READ overlayIconName)
    Q_PROPERTY(QString AttentionIconName READ attentionIconName)

    Q_PROPERTY(int WindowId READ windowId)

// NOT IMPLEMENTED
    Q_PROPERTY(QDBusObjectPath Menu READ menu)

    Q_PROPERTY(IconPixmapList IconPixmap READ iconPixmap)
    Q_PROPERTY(IconPixmapList OverlayIconPixmap READ overlayIconPixmap)
    Q_PROPERTY(IconPixmapList AttentionIconPixmap READ attentionIconPixmap)

    Q_PROPERTY(ToolTip ToolTip READ toolTip)

    Q_PROPERTY(QString AttentionMovieName READ attentionMovieName)

    Q_PROPERTY(QString Category READ category)

    Q_PROPERTY(QString IconThemePath READ iconThemePath)

    Q_PROPERTY(bool ItemIsMenu READ itemIsMenu)

public:
    StatusNotifierItem(QObject *parent = nullptr);
    ~StatusNotifierItem();

    QString id() const
    { return objectName(); }

    QString title() const
    { return m_title; }
    void setTitle(const QString &title);

    QString status() const
    { return m_status; }
    void setStatus(const QString &status);

    QDBusObjectPath menu() const
    { return m_menuPath; }

    QString iconName() const
    { return m_iconName; }
    void setIconByName(const QString &name);

    IconPixmapList iconPixmap() const
    { return m_icon; }

    QString overlayIconName() const
    { return m_overlayIconName; }
    void setOverlayIconByName(const QString &name);

    IconPixmapList overlayIconPixmap() const
    { return m_overlayIcon; }

    QString attentionIconName() const
    { return m_attentionIconName; }
    void setAttentionIconByName(const QString &name);

    IconPixmapList attentionIconPixmap() const
    { return m_attentionIcon; }

    ToolTip toolTip() const
    { return ToolTip(); }

    QString attentionMovieName() const
    { return QString(); }

    QString category() const
    { return QString(); }

    QString iconThemePath() const
    { return QString(); }

    bool itemIsMenu() const
    { return false; }

    int windowId() const
    { return m_serviceCounter; }

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

    // icons
    QString m_iconName, m_overlayIconName, m_attentionIconName;
    IconPixmapList m_icon, m_overlayIcon, m_attentionIcon;
    qint64 m_iconCacheKey, m_overlayIconCacheKey, m_attentionIconCacheKey;

    // menu
    QDBusObjectPath m_menuPath;
    QDBusConnection m_sessionBus;

    static int m_serviceCounter;
    QString m_Title;
    QString m_IconName;
    QString m_OverlayIconName;
    QString m_AttentionIconName;
};

#endif
