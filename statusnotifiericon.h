#ifndef STATUSNOTIFIERICON_H
#define STATUSNOTIFIERICON_H

#include "sniasync.h"

#include <QObject>

#ifndef Q_ENUM
#define Q_ENUM(x) Q_ENUMS(x)
#endif

class StatusNotifierIcon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString icon READ icon NOTIFY iconChanged)
    Q_PROPERTY(QString overlayIcon READ overlayIcon NOTIFY overlayIconChanged)
    Q_PROPERTY(QString attentionIcon READ attentionIcon NOTIFY attentionIconChanged)

public:
    explicit StatusNotifierIcon(const QString &service, const QString &objectPath, QObject *parent = 0);

    enum Status
    {
        Passive,
        Active,
        NeedsAttention
    };
    Q_ENUM(Status)

    Status status() const;
    QString icon() const;
    QString overlayIcon() const;
    QString attentionIcon() const;
    QString title() const;

public slots:
    void activate();
    void secondaryActivate();
    void scroll(int delta, Qt::Orientation orientation = Qt::Vertical);

signals:
    void statusChanged(Status status);
    void iconChanged(const QString &icon);
    void overlayIconChanged(const QString &overlayIcon);
    void attentionIconChanged(const QString &attentionIcon);
    void titleChanged(const QString &title);

private slots:
    void newIcon();
    void newAttentionIcon();
    void newOverlayIcon();
    void newTitle();
    void newStatus(const QString &status);

private:
    void refetchIcon(Status status);

    SniAsync *m_interface;
    Status m_status;
    QString m_icon, m_overlayIcon, m_attentionIcon;
    QString m_title;
};

#endif // STATUSNOTIFIERICON_H
