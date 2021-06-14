#include "GuildsModel.hpp"

GuildsModel::GuildsModel(QList<Guild> *g, QObject *parent) :
    QAbstractListModel(parent), m_guilds{ g }
{
}

int GuildsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (m_guilds == nullptr) {
        return 0;
    }

    return m_guilds->size();
}

#include <QImage>

QVariant GuildsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_guilds == nullptr) {
        return {};
    }

    if (role == Role::Name) {
        return m_guilds->at(index.row()).name();
    }

    if (role == Role::Icon) {
        QImage img;
        img.loadFromData(m_guilds->at(index.row()).icondata());
        return img;
    }

    return {};
}

QHash<int, QByteArray> GuildsModel::roleNames() const
{
    return { { Role::Name, "nameRole" }, { Role::Icon, "iconRole" } };
}

void GuildsModel::select(int index)
{
    m_selected = index;
    emit selectedChanged();

    m_channelsModel.setChannels(&(*m_guilds)[m_selected].channels);
}

int GuildsModel::selected() const
{
    return m_selected;
}

snowflake GuildsModel::selectedID() const
{
    return m_guilds->at(selected()).id();
}

ChannelsModel *GuildsModel::channelsModel()
{
    return &m_channelsModel;
}

void GuildsModel::setViewMode(GuildsModel::ViewMode vm)
{
    m_viewMode = vm;
    emit viewModeChanged();
}

GuildsModel::ViewMode GuildsModel::viewMode() const noexcept
{
    return m_viewMode;
}

void GuildsModel::setViewIconDirection(GuildsModel::ViewIconDirection vdir)
{
    m_viewIconDirection = vdir;
    emit viewIconDirectionChanged();
}

GuildsModel::ViewIconDirection GuildsModel::viewIconDirection() const noexcept
{
    return m_viewIconDirection;
}

void GuildsModel::updateGuildIcon()
{
    if (m_viewMode == ViewMode::Icon) {
        emit dataChanged(index(0, 0), index(this->rowCount() - 1, 0),
                         { Role::Icon });
    }
}

void GuildsModel::updateMessages()
{
    m_channelsModel.updateMessages();
}
