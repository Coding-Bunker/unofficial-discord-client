#pragma once

#include "core/Settings.hpp"

#include <QAbstractListModel>

class SettingsModel : public QAbstractListModel
{
    // clang-format off
    Q_OBJECT
    // clang-format on

  public:
    explicit SettingsModel(QObject *parent = nullptr);

    void setSettings(Settings *set);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;

    enum Role { Description = Qt::UserRole + 1, Type, Choices, StartValue };

    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void setParameter(int indexOfParam, int valueOfChoices);

  private:
    Settings *m_setting;
};
