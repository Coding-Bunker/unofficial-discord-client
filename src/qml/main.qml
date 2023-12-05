import QtQuick
import QtQuick.Window
import QtQuick.Controls

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Quit")
                shortcut: Shortcut {
                    sequence: StandardKey.Quit
                    context: Qt.ApplicationShortcut
                }
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("&Settings")
            Action {
                text: qsTr("&Preferences")
                shortcut: Shortcut {
                    sequence: "Ctrl+S" // TODO: change this with StandardKey.Preferences
                    context: Qt.ApplicationShortcut
                }
                onTriggered: stackview.push(settings)
                enabled: stackview.currentItem.objectName === settings.objectName
            }
        }

        Menu {
            title: qsTr("&Help")
            Action {
                text: qsTr("&About")
            }
        }
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
            var popupMessageError = popupComponent.createObject(stackview)
            popupMessageError.open()
            popupMessageError.title = qsTr(title)
            popupMessageError.message = qsTr(errorMessage)
        }
    }
}
