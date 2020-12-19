#include "MessagesModel.hpp"

MessagesModel::MessagesModel(QObject *parent) : QAbstractListModel(parent) {}

void MessagesModel::setMessages(QList<Message> *msg)
{
    beginResetModel();
    m_messages = msg;
    endResetModel();
}

int MessagesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (m_messages == nullptr) {
        return 0;
    }

    return m_messages->size();
}

QVariant MessagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_messages == nullptr) {
        return {};
    }

    switch (role) {
        case Role::Author:
            return m_messages->at(index.row()).author();

        case Role::Content:
            return m_messages->at(index.row()).content();
    }

    return {};
}

QHash<int, QByteArray> MessagesModel::roleNames() const
{
    return { { Role::Author, "authorRole" }, { Role::Content, "contentRole" } };
}
