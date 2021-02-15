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
            anchors.fill: parent
            model: hmi.guildsModel
            visible: hmi.guildModelVisible
            clip: true
            boundsBehavior: ListView.StopAtBounds
            delegate: Text {
                text: nameRole
                color: hmi.guildsModel.selected ===
                    index ? Material.accentColor : Material.foreground
                MouseArea {
                    anchors.fill: parent
                    onClicked: hmi.guildsModel.select(index)
                }
            }
        }
    }
}