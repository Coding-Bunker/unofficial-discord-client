import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {
    color: Material.backgroundColor
    anchors.fill: parent

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

        model: 1
        delegate: Row {
            spacing: 5

            Text {
                text: "Guilds as:"
                color: Material.foreground
                font.bold: true
            }

            Text {
                text: "icon"
                color: Material.foreground
            }
        }
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
