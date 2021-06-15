import QtQuick
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
             clip: true
             model: hml.guildsModel.channelsModel
             boundsBehavior: ListView.StopAtBounds
        }
    }
}
