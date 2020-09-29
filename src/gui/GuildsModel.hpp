#pragma once

#include "core/Guild.hpp"

#include <QAbstractListModel>

class GuildsModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    explicit GuildsModel(const QVector<Guild> &g, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    enum Role { Name = Qt::UserRole + 1 };

    QHash<int, QByteArray> roleNames() const override;

  private:
    const QVector<Guild> &m_guilds;
};
