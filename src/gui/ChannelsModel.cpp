#include "ChannelsModel.hpp"

ChannelsModel::ChannelsModel(QObject *parent) : QAbstractListModel(parent) {}

void ChannelsModel::setChannels(const QList<Channel> &c)
{
    beginResetModel();
    m_channels = c;
    endResetModel();
    resetSelected();
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

    const auto pos = std::find_if(
        m_channels.begin(), m_channels.end(),
        [&](const Channel &c) { return c.position() == m_selected; });

    if (pos == m_channels.end()) {
        qWarning() << Q_FUNC_INFO << "can't request messages for this channel";
        return;
    }

    const auto idx = std::distance(m_channels.begin(), pos);
    emit requestMessages(m_channels[idx].id());
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
