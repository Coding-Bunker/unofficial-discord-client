#pragma once

#include "core/Channel.hpp"
#include "gui/MessagesModel.hpp"

#include <QAbstractListModel>

class ChannelsModel : public QAbstractListModel
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(int selected READ selected NOTIFY selectedChanged)
    Q_PROPERTY(MessagesModel* msgModel READ msgModel NOTIFY msgModelChanged)
    // clang-format on

  public:
    explicit ChannelsModel(QObject *parent = nullptr);

    void setChannels(QList<Channel> *c);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    enum Role { Name = Qt::UserRole + 1 };

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void select(int index);
    Q_INVOKABLE void sendMsg(QString &txt);

    int selected() const;
    MessagesModel *msgModel();

    void updateMessages();

  signals:
    void selectedChanged();
    void requestMessages(snowflake channelID);
    void msgModelChanged();
    void sendMessage(snowflake channelID, QString txt);

  private:
    QList<Channel> *m_channels{ nullptr };
    int m_selected{ -1 };
    MessagesModel m_msgModel;

    void resetSelected();
};
