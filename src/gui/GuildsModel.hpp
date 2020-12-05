#pragma once

#include "core/Guild.hpp"

#include <QAbstractListModel>

class GuildsModel : public QAbstractListModel
{
    // clang-format off
    Q_OBJECT
    Q_PROPERTY(int selected READ selected NOTIFY selectedChanged)
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

  signals:
    void selectedChanged();

  private:
    const QList<Guild> &m_guilds;
    int m_selected;
};
