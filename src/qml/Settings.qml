import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.qmlmodels 1.0

Rectangle {
    color: Material.backgroundColor

    Text {
        id: title

        text: qsTr("Settings")
        anchors {
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            top: parent.top
        }

        color: Material.foreground
        font.bold: true
        font.pixelSize: 24
    }

    ListView {
        anchors {
            top: title.bottom
            bottom: okButton.top
        }

        model: settingsModel

        DelegateChooser {
            id: chooser

            role: "typeRole"

            DelegateChoice {
                roleValue: 0
                Row {
                    spacing: 5

                    Text {
                        text: descriptionRole
                        color: Material.foreground
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    ComboBox {
                        model: choicesRole
                        anchors.verticalCenter: parent.verticalCenter
                        onActivated: console.log("activated", currentIndex)
                    }
                }
            }
        }

        delegate: chooser
    }

    Button {
        id: okButton

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottomMargin: 10
            bottom: parent.bottom
        }

        width: parent.width * .3
        height: parent.height * .1

        text: qsTr("Ok")
        onClicked: stackview.pop()
    }
}
