#include "GuildsModel.hpp"

GuildsModel::GuildsModel(QList<Guild> &g, QObject *parent) :
    QAbstractListModel(parent), m_guilds{ g }
{
}

int GuildsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_guilds.size();
}

QVariant GuildsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (role == Role::Name) {
        return m_guilds.at(index.row()).name();
    }

    return {};
}

QHash<int, QByteArray> GuildsModel::roleNames() const
{
    return { { Role::Name, "nameRole" } };
}

void GuildsModel::select(int index)
{
    m_selected = index;
    emit selectedChanged();

    m_channelsModel.setChannels(m_guilds[m_selected].channels);
}

int GuildsModel::selected() const
{
    return m_selected;
}

snowflake GuildsModel::selectedID() const
{
    return m_guilds.at(selected()).id();
}

ChannelsModel *GuildsModel::channelsModel()
{
    return &m_channelsModel;
}
