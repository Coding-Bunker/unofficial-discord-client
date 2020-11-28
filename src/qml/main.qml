import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }

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

    Login {
        anchors.centerIn: parent
    }
}
