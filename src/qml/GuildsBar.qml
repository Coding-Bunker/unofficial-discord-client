import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import Qt.labs.qmlmodels 1.0

import ui 1.0

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

            delegate: Item {
                height: txt.visible ? txt.height : img.height

                Image {
                    id: img

                    visible: hmi.guildsModel.viewMode === ViewMode.Icon
                    width: 32
                    height: 32
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    source: iconRole
                }

                Text {
                    id: txt

                    visible: hmi.guildsModel.viewMode === ViewMode.Text
                    text: nameRole
                    color: hmi.guildsModel.selected
                           === index ? Material.accentColor : Material.foreground
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: hmi.guildsModel.select(index)
                }
            }
        }
    }
}
