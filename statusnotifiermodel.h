#ifndef STATUSNOTIFIERMODEL_H
#define STATUSNOTIFIERMODEL_H

#include "statusnotifierhost.h"
#include "statusnotifiericon.h"

#include <QAbstractListModel>
#include <QObject>

class StatusNotifierModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit StatusNotifierModel(QObject *parent = 0);

    int rowCount(const QModelIndex &) const { return m_modelData.count(); }
    QVariant data(const QModelIndex &index, int = Qt::UserRole) const;
    QHash<int, QByteArray> roleNames() const { return m_roles; }

private slots:
    void onItemAdded(StatusNotifierIcon* item);
    void onItemRemoved(StatusNotifierIcon* item);

private:
    QList<StatusNotifierIcon*> m_modelData;
    QHash<int, QByteArray> m_roles;

    StatusNotifierHost* m_host;
};

#endif // STATUSNOTIFIERMODEL_H
