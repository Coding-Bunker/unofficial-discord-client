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

    Shortcut {
        sequence: "Ctrl+S"
        context: Qt.ApplicationShortcut
        onActivated: stackview.push(settings)
        enabled: stackview.currentItem.objectName === settings.objectName
    }

    StackView {
        id: stackview

        anchors.fill: parent

        Component {
            id: login

            Login {}
        }

        Component {
            id: chat

            Chat {}
        }

        Component {
            id: settings

            Settings {}
        }

        initialItem: login
    }

    Connections {
        target: hmi
        function onLoginSuccess() {
            stackview.push(chat)
        }
    }
}