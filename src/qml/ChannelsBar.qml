import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material

Rectangle {
    color: Material.backgroundColor
    width: parent.width * 0.2

    Rectangle {
        color: Material.primaryColor
        anchors.centerIn: parent
        height: parent.height - 10
        width: parent.width - 10

        ListView {
            anchors.fill: parent
            model: hmi.guildsModel.channelsModel
            visible: hmi.guildModelVisible && hmi.guildsModel.selected !== -1
            clip: true
            boundsBehavior: ListView.StopAtBounds
            delegate: Text {
                text: nameRole
                color: hmi.guildsModel.channelsModel.selected
                       === index ? Material.accentColor : Material.foreground

                MouseArea {
                    anchors.fill: parent
                    onClicked: hmi.guildsModel.channelsModel.select(index)
                }
            }
        }
    }
}
