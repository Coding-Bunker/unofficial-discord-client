#include "ChannelsModel.hpp"

ChannelsModel::ChannelsModel(const QList<Channel> &c, QObject *parent) :
    QAbstractListModel(parent), m_channels{ c }
{
}

int ChannelsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_channels.size();
}

QVariant ChannelsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (role == Role::Name) {
        return m_channels.at(index.row()).name();
    }

    return {};
}

QHash<int, QByteArray> ChannelsModel::roleNames() const
{
    return { { Role::Name, "nameRole" } };
}

void ChannelsModel::select(int index)
{
    m_selected = index;
    emit selectedChanged();
}

int ChannelsModel::selected() const
{
    return m_selected;
}

void ChannelsModel::resetSelected()
{
    m_selected = -1;
    emit selectedChanged();
}
