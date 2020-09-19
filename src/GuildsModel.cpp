#include "GuildsModel.hpp"

GuildsModel::GuildsModel(const QVector<Guild> &g, QObject *parent) :
    QAbstractListModel(parent), m_guilds{ g }
{}

int GuildsModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 0;
    }

    qDebug() << m_guilds.size();
    return m_guilds.size();
}

QVariant GuildsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    qDebug() << "pass here";
    if (role == Qt::DisplayRole) {
        qDebug() << m_guilds.at(index.row()).name();
        return m_guilds.at(index.row()).name();
    }

    return {};
}
