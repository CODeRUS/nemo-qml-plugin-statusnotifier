#include "statusnotifiermodel.h"

StatusNotifierModel::StatusNotifierModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_host(new StatusNotifierHost(this))
{
    m_roles[Qt::UserRole] = QByteArrayLiteral("notifierItem");

    connect(m_host, &StatusNotifierHost::itemAdded, this, &StatusNotifierModel::onItemAdded);
    connect(m_host, &StatusNotifierHost::itemRemoved, this, &StatusNotifierModel::onItemRemoved);
}

QVariant StatusNotifierModel::data(const QModelIndex &index, int) const
{
    int row = index.row();
    if (row < 0 || row >= m_modelData.count())
        return QVariant();
    StatusNotifierIcon *icon = m_modelData[row];
    return QVariant::fromValue(icon);
}

void StatusNotifierModel::onItemAdded(StatusNotifierIcon *item)
{
    if (m_modelData.contains(item)) {
        return;
    }

    beginInsertRows(QModelIndex(), m_modelData.count(), m_modelData.count());
    m_modelData.append(item);
    endInsertRows();
}

void StatusNotifierModel::onItemRemoved(StatusNotifierIcon *item)
{
    if (!m_modelData.contains(item)) {
        return;
    }

    int index = m_modelData.indexOf(item);
    beginRemoveRows(QModelIndex(), index, index);
    m_modelData.removeAt(index);
    endRemoveRows();
}
