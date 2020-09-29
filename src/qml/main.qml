import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: application.name

    // TODO(guerra): move to other file
    Rectangle {
        visible: user.logged
        anchors {
            top: parent.top
            left: parent.lef
            right: parent.right
        }

        height: parent.height * 0.1
        width: parent.width
        color: "black"

        Text {
            text: user.username
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            color: "gray"
            font.pixelSize: 20
        }
    }

    // TODO(guerra): move to other file
    Rectangle {
        visible: user.logged
        anchors {
            top: parent.top
            left: parent.left
            bottom: parent.bottom
        }

        width: parent.width * 0.1
        color: "black"

        ListView {
            anchors.fill: parent
            model: hmi.guildsModel
            delegate: Text {
                width: parent.width * 0.9
                height: width
                text: nameRole
                color: "gray"
            }
        }
    }

    Button {
        anchors.centerIn: parent
        width: 100
        height: 100
        onClicked: auth.requestLogin()
        text: "Login..."
        visible: !user.logged
    }
}
