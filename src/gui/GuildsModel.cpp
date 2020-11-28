#include "GuildsModel.hpp"

GuildsModel::GuildsModel(const QVector<Guild> &g, QObject *parent) :
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
}

int GuildsModel::selected() const
{
    return m_selected;
}
