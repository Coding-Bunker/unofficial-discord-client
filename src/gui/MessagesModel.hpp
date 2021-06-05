#pragma once

#include "core/Message.hpp"

#include <QAbstractListModel>

class MessagesModel : public QAbstractListModel
{
    // clang-format off
    Q_OBJECT
    // clang-format on

  public:
    explicit MessagesModel(QObject *parent = nullptr);

    void setMessages(QList<Message> *msg);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    enum Role { Author = Qt::UserRole + 1, Content };

    QHash<int, QByteArray> roleNames() const override;

  private:
    QList<Message>* m_messages{nullptr};
};
