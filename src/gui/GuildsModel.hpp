#pragma once

#include "ChannelsModel.hpp"
#include "core/Guild.hpp"

#include <QAbstractListModel>

class GuildsModel : public QAbstractListModel
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(int selected READ selected NOTIFY selectedChanged)
    Q_PROPERTY(ChannelsModel *channelsModel READ channelsModel CONSTANT)
    // clang-format on

  public:
    explicit GuildsModel(const QList<Guild> &g, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    enum Role { Name = Qt::UserRole + 1 };

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void select(int index);

    int selected() const;

    ChannelsModel *channelsModel();

  signals:
    void selectedChanged();

  private:
    const QList<Guild> &m_guilds;
    int m_selected{ -1 };
    ChannelsModel m_channelsModel;

    void createChannelModel(const QList<Channel> &c);
};
