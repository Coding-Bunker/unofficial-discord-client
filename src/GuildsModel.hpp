#pragma once

#include "Guild.hpp"

#include <QAbstractListModel>

class GuildsModel : public QAbstractListModel
{
    Q_OBJECT

  public:
    explicit GuildsModel(const QVector<Guild> &g, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

  private:
    const QVector<Guild> &m_guilds;
};
