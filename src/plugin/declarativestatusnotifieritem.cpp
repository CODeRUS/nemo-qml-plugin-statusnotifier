#include "declarativestatusnotifieritem.h"

DeclarativeStatusNotifierItem::DeclarativeStatusNotifierItem(QObject *parent)
    : QObject(parent)
    , m_item(new StatusNotifierItem(QStringLiteral("ApplicationStatus"), false, QStringLiteral("/MenuNotImplemented"), this))
{
    connect(m_item, &StatusNotifierItem::activateRequested, this, &DeclarativeStatusNotifierItem::activateRequested);
    connect(m_item, &StatusNotifierItem::secondaryActivateRequested, this, &DeclarativeStatusNotifierItem::secondaryActivateRequested);
    connect(m_item, &StatusNotifierItem::scrollRequested, this, &DeclarativeStatusNotifierItem::scrollRequested);
}

DeclarativeStatusNotifierItem::Status DeclarativeStatusNotifierItem::status()
{
    return statusToEnum(m_item->status());
}

QString DeclarativeStatusNotifierItem::title()
{
    return m_item->title();
}

QString DeclarativeStatusNotifierItem::icon()
{
    return m_item->iconName();
}

QString DeclarativeStatusNotifierItem::overlayIcon()
{
    return m_item->overlayIconName();
}

QString DeclarativeStatusNotifierItem::attentionIcon()
{
    return m_item->attentionIconName();
}

DeclarativeStatusNotifierItem::Status DeclarativeStatusNotifierItem::statusToEnum(const QString &status)
{
    if (status == QStringLiteral("Active")) {
        return ActiveStatus;
    } else if (status == QStringLiteral("NeedsAttention")) {
        return NeedsAttentionStatus;
    } else {
        return PassiveStatus;
    }
}

QString DeclarativeStatusNotifierItem::statusToString(DeclarativeStatusNotifierItem::Status status) const
{
    switch (status) {
    case ActiveStatus:
        return QStringLiteral("Active");
    case NeedsAttentionStatus:
        return QStringLiteral("NeedsAttention");
    case PassiveStatus:
        return QStringLiteral("Passive");
    default:
        return QString();
    }
}

void DeclarativeStatusNotifierItem::setStatus(DeclarativeStatusNotifierItem::Status value)
{
    if (status() == value)
        return;

    m_item->setStatus(statusToString(value));
    emit statusChanged(value);
}

void DeclarativeStatusNotifierItem::setTitle(const QString &value)
{
    if (title() == value)
        return;

    m_item->setTitle(value);
    emit titleChanged(value);
}

void DeclarativeStatusNotifierItem::setIcon(const QString &value)
{
    if (icon() == value)
        return;

    m_item->setIconByName(value);
    emit iconChanged(value);
}

void DeclarativeStatusNotifierItem::setOverlayIcon(const QString &value)
{
    if (overlayIcon() == value)
        return;

    m_item->setOverlayIconByName(value);
    emit overlayIconChanged(value);
}

void DeclarativeStatusNotifierItem::setAttentionIcon(const QString &value)
{
    if (attentionIcon() == value)
        return;

    m_item->setAttentionIconByName(value);
    emit attentionIconChanged(value);
}
