import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
//import "Menubar" as Private

ApplicationWindow {
    width: 640
    height: 480
    visible: true

    // Kludge
    Loader {
        id: kludge
        source: "Menubar.qml"
    }

    menuBar: kludge.item

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

        function onShowError(title, errorMessage) {
            var popupComponent = Qt.createComponent("qrc:/PopupMessage.qml")
            var popupMessageError = popupComponent.createObject(stackview);
            popupMessageError.open()
            popupMessageError.title = qsTr(title)
            popupMessageError.message = qsTr(errorMessage)
        }
    }
}