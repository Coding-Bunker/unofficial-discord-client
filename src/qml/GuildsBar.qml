import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    visible: user.logged

    width: parent.width * 0.1
    color: "black"

    ListView {
        anchors.fill: parent
        model: hmi.guildsModel
        contentItem.width: width * 0.9
        contentItem.height: width
        delegate: Text {
            text: nameRole
            color: "gray"
        }
    }
}
