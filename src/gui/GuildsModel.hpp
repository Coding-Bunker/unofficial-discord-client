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
    Q_PROPERTY(ViewMode viewMode READ viewMode NOTIFY viewModeChanged)
    Q_ENUMS(ViewMode)
    // clang-format on

  public:
    explicit GuildsModel(QList<Guild> *g, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    enum Role { Name = Qt::UserRole + 1, Icon };

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void select(int index);

    int selected() const;
    snowflake selectedID() const;

    ChannelsModel *channelsModel();

    enum class ViewMode { Text, Icon };

    void setViewMode(ViewMode vm);
    ViewMode viewMode() const noexcept;

    void updateGuildIcon();

  signals:
    void selectedChanged();
    void viewModeChanged();

  public slots:
    void updateMessages();

  private:
    QList<Guild> *m_guilds;
    int m_selected{ -1 };
    ChannelsModel m_channelsModel;
    ViewMode m_viewMode;
};
