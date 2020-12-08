import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

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
