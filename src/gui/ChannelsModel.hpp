#pragma once

#include "core/Channel.hpp"

#include <QAbstractListModel>

class ChannelsModel : public QAbstractListModel
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(int selected READ selected NOTIFY selectedChanged)
    // clang-format on

  public:
    explicit ChannelsModel(QObject *parent = nullptr);

    void setChannels(const QList<Channel> &c);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    enum Role { Name = Qt::UserRole + 1 };

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void select(int index);

    int selected() const;

  signals:
    void selectedChanged();
    void requestMessages(snowflake channelID);

  private:
    QList<Channel> m_channels;
    int m_selected{ -1 };

    void resetSelected();
};
