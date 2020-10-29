import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    visible: user.logged

    height: parent.height * 0.03
    width: parent.width
    color: "black"

    Text {
        text: user.username
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        color: "gray"
        font.pixelSize: 14
    }
}
