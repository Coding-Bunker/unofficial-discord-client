import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    color: "black"
    height: parent.height * 0.1
    visible: user.logged

    ListView {
        anchors.fill: parent
        model: hmi.guildsModel
        clip: true
        boundsBehavior: ListView.StopAtBounds
        delegate: Text {
            text: nameRole
            font.pixelSize: 16
            color: hmi.guildsModel.selected === index ? "white" : "green"

            MouseArea {
                anchors.fill: parent
                onClicked: hmi.guildsModel.select(index)
            }
        }
    }
}
