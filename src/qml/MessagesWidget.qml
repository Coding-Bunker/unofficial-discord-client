import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {
    color: Material.backgroundColor
    height: parent.height * 0.1

    Rectangle {
        color: Material.primaryColor
        anchors.centerIn: parent
        height: parent.height - 10
        width: parent.width - 10

        ListView {
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }

            model: hmi.guildsModel.channelsModel.msgModel
            visible: hmi.guildModelVisible && hmi.guildsModel.selected !== -1
            delegate: Row {

                spacing: 5

                Text {
                    text: authorRole + ":"
                    color: Material.foreground
                    font.bold: true
                }

                Text {
                    text: contentRole
                    color: Material.foreground
                }
            }
        }

        SendMessageWidget {
            anchors.bottom: parent.bottom
        }
    }
}