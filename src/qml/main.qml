import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    background: Rectangle {
        anchors.fill: parent
        color: "darkgray"
    }

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }

    UserInfoBar {
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
    }

    GuildsBar {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }
    }

    Button {
        anchors.centerIn: parent
        width: 100
        height: 100
        onClicked: auth.requestLogin()
        text: "Login..."
        visible: !user.logged
    }
}
