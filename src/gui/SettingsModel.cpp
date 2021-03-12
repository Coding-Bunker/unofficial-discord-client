#include "SettingsModel.hpp"

SettingsModel::SettingsModel(QObject *parent) : QAbstractListModel(parent) {}

void SettingsModel::setSettings(Settings *set)
{
    m_setting = set;
}

int SettingsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return m_setting->parameters().size();
}

QVariant SettingsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_setting == nullptr) {
        return {};
    }

    if (role == Role::Description) {
        return m_setting->parameters()[index.row()].description;
    }

    if (role == Role::Type) {
        return m_setting->parameters()[index.row()].type;
    }

    if (role == Role::Choices) {
        return m_setting->parameters()[index.row()].possibleValues;
    }

    return {};
}

QHash<int, QByteArray> SettingsModel::roleNames() const
{
    return { { Role::Description, "descriptionRole" },
             { Role::Type, "typeRole" },
             { Role::Choices, "choicesRole" } };
}

void SettingsModel::setParameter(int indexOfParam, int valueOfChoices)
{
    m_setting->setParameter(indexOfParam, valueOfChoices);
}
