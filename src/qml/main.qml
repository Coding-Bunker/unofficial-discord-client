import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
//import "Menubar" as Private

ApplicationWindow {
    width: 640
    height: 480
    visible: true

    Menubar {
        id: mb
    }

    menuBar: mb

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
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
