import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {
    color: Material.backgroundColor
    height: parent.height * 0.03
    width: parent.width

    Rectangle {
        id: inner

        color: Material.primaryColor
        anchors.centerIn: parent
        height: parent.height - 10
        width: parent.width - 10

        Text {
            text: user.username
            anchors {
                right: logoutBtn.left
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            color: Material.accentColor
            font.pixelSize: 14
        }

        Button {
            id: logoutBtn

            text: "logout"
            height: parent.height * 1.2
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            onClicked: auth.requestLogout()
        }
    }
}
