#ifndef DECLARATIVESTATUSNOTIFIERITEM_H
#define DECLARATIVESTATUSNOTIFIERITEM_H

#include "statusnotifieritem.h"

#include <QObject>
#include <QPoint>

#ifndef Q_ENUM
#define Q_ENUM(x) Q_ENUMS(x)
#endif

class DeclarativeStatusNotifierItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
    Q_PROPERTY(QString overlayIcon READ overlayIcon WRITE setOverlayIcon NOTIFY overlayIconChanged)
    Q_PROPERTY(QString attentionIcon READ attentionIcon WRITE setAttentionIcon NOTIFY attentionIconChanged)

public:
    explicit DeclarativeStatusNotifierItem(QObject *parent = 0);

    enum Status
    {
        PassiveStatus,
        ActiveStatus,
        NeedsAttentionStatus
    };
    Q_ENUM(Status)

signals:
    void statusChanged(Status status);
    void titleChanged(const QString &title);
    void iconChanged(const QString &icon);
    void overlayIconChanged(const QString &overlayIcon);
    void attentionIconChanged(const QString &attentionIcon);

    void activateRequested(const QPoint &pos);
    void secondaryActivateRequested(const QPoint &pos);
    void scrollRequested(int delta, Qt::Orientation orientation);

private:
    Status status();
    QString title();
    QString icon();
    QString overlayIcon();
    QString attentionIcon();

    void setStatus(Status value);
    void setTitle(const QString &value);
    void setIcon(const QString &value);
    void setOverlayIcon(const QString &value);
    void setAttentionIcon(const QString &value);

    Status statusToEnum(const QString &status);
    QString statusToString(Status status) const;

    StatusNotifierItem *m_item;

};

#endif // DECLARATIVESTATUSNOTIFIERITEM_H
