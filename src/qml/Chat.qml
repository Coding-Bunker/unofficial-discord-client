import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {

    color: Material.backgroundColor

    UserInfoBar {
        id: userInfo

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
    }

    GuildsBar {
        id: guildsBar

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    MessagesWidget {
        id: msgWidget

        anchors {
            top: guildsBar.bottom
            right: parent.right
            left: channelsBar.right
            bottom: userInfo.top
        }

    }

    ChannelsBar {
        id: channelsBar

        anchors {
            left: parent.left
            top: guildsBar.bottom
            bottom: userInfo.top
        }
    }
}
