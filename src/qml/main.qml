import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: application.name

    Rectangle {
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

    Button {
        anchors.centerIn: parent
        width: 100
        height: 100
        onClicked: auth.requestLogin()
        text: "Login..."
    }
}
