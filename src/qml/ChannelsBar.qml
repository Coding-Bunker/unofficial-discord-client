import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {
    color: Material.backgroundColor
    visible: user.logged
    width: parent.width * 0.2

    Rectangle {
        color: Material.primaryColor
        anchors.centerIn: parent
        height: parent.height - 10
        width: parent.width - 10

        ListView {
            anchors.fill: parent
            model: 20
            clip: true
            boundsBehavior: ListView.StopAtBounds
            delegate: Text {
                text: "this is a channel " + index
                color: Material.foreground

                MouseArea {
                    anchors.fill: parent
                }
            }
        }
    }
}
