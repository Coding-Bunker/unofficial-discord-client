#include "MessagesModel.hpp"

MessagesModel::MessagesModel(QObject *parent) : QAbstractListModel(parent) {}

int MessagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_messages->size();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (role == Role::Author) {
        return m_messages->at(index.row()).author();
    }

    return {};
}

QHash<int, QByteArray> MessagesModel::roleNames() const
{
    return { { Role::Author, "authorRole" } };
}
