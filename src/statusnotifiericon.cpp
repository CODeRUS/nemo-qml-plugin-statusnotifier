#include "statusnotifiericon.h"
#include "sniasync.h"

#include <QDBusPendingCallWatcher>
#include <QDBusPendingReply>
#include <QDebug>

StatusNotifierIcon::StatusNotifierIcon(const QString &service, const QString &objectPath, QObject *parent)
    : QObject(parent)
    , m_status(Passive)
{
    m_interface = new SniAsync(service, objectPath, QDBusConnection::sessionBus(), this);

    connect(m_interface, &SniAsync::NewIcon, this, &StatusNotifierIcon::newIcon);
    connect(m_interface, &SniAsync::NewOverlayIcon, this, &StatusNotifierIcon::newOverlayIcon);
    connect(m_interface, &SniAsync::NewAttentionIcon, this, &StatusNotifierIcon::newAttentionIcon);
    connect(m_interface, &SniAsync::NewTitle, this, &StatusNotifierIcon::newTitle);
    connect(m_interface, &SniAsync::NewStatus, this, &StatusNotifierIcon::newStatus);

    m_interface->propertyGetAsync(QStringLiteral("Status"), [this] (QString status) {
        newStatus(status);
    });

    newTitle();

    refetchIcon(Active);
    refetchIcon(Passive);
    refetchIcon(NeedsAttention);
}

StatusNotifierIcon::Status StatusNotifierIcon::status() const
{
    return m_status;
}

QString StatusNotifierIcon::icon() const
{
    return m_icon;
}

QString StatusNotifierIcon::overlayIcon() const
{
    return m_overlayIcon;
}

QString StatusNotifierIcon::attentionIcon() const
{
    return m_attentionIcon;
}

QString StatusNotifierIcon::title() const
{
    return m_title;
}

void StatusNotifierIcon::activate()
{
    m_interface->Activate(0, 0);
}

void StatusNotifierIcon::secondaryActivate()
{
    m_interface->SecondaryActivate(0, 0);
}

void StatusNotifierIcon::scroll(int delta, Qt::Orientation orientation)
{
    m_interface->Scroll(delta, orientation == Qt::Horizontal ? QStringLiteral("horizontal") : QStringLiteral("vertical"));
}

void StatusNotifierIcon::newIcon()
{
    refetchIcon(Passive);
}

void StatusNotifierIcon::newAttentionIcon()
{
    refetchIcon(NeedsAttention);
}

void StatusNotifierIcon::newOverlayIcon()
{
    refetchIcon(Active);
}

void StatusNotifierIcon::newTitle()
{
    m_interface->propertyGetAsync(QStringLiteral("Title"), [this] (QString title) {
        qDebug() << title;
        m_title = title;
        emit titleChanged(m_title);
    });
}

void StatusNotifierIcon::newStatus(const QString &status)
{
    qDebug() << status;

    Status newStatus;
    if (status == QStringLiteral("NeedsAttention"))
        newStatus = NeedsAttention;
    else if (status == QStringLiteral("Active"))
        newStatus = Active;
    else
        newStatus = Passive;

    if (m_status == newStatus)
        return;

    m_status = newStatus;
    emit statusChanged(m_status);
}

void StatusNotifierIcon::refetchIcon(StatusNotifierIcon::Status status)
{
    QString nameProperty;
    switch (status)
    {
        case Active:
            nameProperty = QStringLiteral("OverlayIconName");
            break;
        case NeedsAttention:
            nameProperty = QStringLiteral("AttentionIconName");
            break;
        case Passive:
            nameProperty = QStringLiteral("IconName");
            break;
    }

    m_interface->propertyGetAsync(nameProperty, [this, status] (QString iconName) {
        qDebug() << status << iconName;
        switch (status)
        {
            case Active:
                m_overlayIcon = iconName;
                emit overlayIconChanged(m_overlayIcon);
                break;
            case NeedsAttention:
                m_attentionIcon = iconName;
                emit attentionIconChanged(m_attentionIcon);
                break;
            case Passive:
                m_icon = iconName;
                emit iconChanged(m_icon);
                break;
        }
    });
}

