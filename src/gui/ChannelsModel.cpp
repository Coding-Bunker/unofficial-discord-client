#include "ChannelsModel.hpp"

ChannelsModel::ChannelsModel(QObject *parent) : QAbstractListModel(parent) {}

void ChannelsModel::setChannels(QList<Channel> *c)
{
    beginResetModel();
    m_channels = c;
    endResetModel();
    resetSelected();
}

int ChannelsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    if (m_channels == nullptr) {
        return 0;
    }

    return m_channels->size();
}

QVariant ChannelsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || m_channels == nullptr) {
        return {};
    }

    if (role == Role::Name && m_channels->at(index.row()).name()) {
        return m_channels->at(index.row()).name().value();
    }

    return {};
}

QHash<int, QByteArray> ChannelsModel::roleNames() const
{
    return { { Role::Name, "nameRole" } };
}

void ChannelsModel::select(int index)
{
    m_selected = index;
    emit selectedChanged();

    // clazy:excludeall=detaching-member
    const auto pos{ std::find_if(
        m_channels->begin(), m_channels->end(),
        [&](const Channel &c) { return c.position() == m_selected; }) };

    if (pos == m_channels->end()) {
        qWarning() << Q_FUNC_INFO << "can't request messages for this channel";
        return;
    }

    const auto idx = std::distance(m_channels->begin(), pos);
    emit requestMessages(m_channels->at(idx).id());
}

void ChannelsModel::sendMsg(QString &txt)
{
    if (m_selected == -1) {
        return;
    }

    emit sendMessage(m_channels->at(m_selected).id(), txt);
}

int ChannelsModel::selected() const
{
    return m_selected;
}

MessagesModel *ChannelsModel::msgModel()
{
    return &m_msgModel;
}

void ChannelsModel::updateMessages()
{
    m_msgModel.setMessages(&(*m_channels)[m_selected].messages);
}

void ChannelsModel::resetSelected()
{
    m_selected = -1;
    emit selectedChanged();
}
