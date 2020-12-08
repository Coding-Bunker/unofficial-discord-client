import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {

    color: Material.backgroundColor

    Rectangle {
        id: circle

        anchors.centerIn: parent
        height: parent.height / 2
        width: height
        radius: height / 2
        color: "#fdfff5"
        border.color: Material.primaryColor
        border.width: 10

        readonly property int itemHeight: 17
        readonly property int itemWidth: 250

        Row {
            id: row
            spacing: 10
            anchors.centerIn: parent

            Column {
                spacing: 10

                Text {
                    text: qsTr("Email:")
                }

                Text {
                    text: qsTr("Password:")
                }

                Text {
                    text: qsTr("2FA code (only if you have):")
                }
            }

            Column {
                spacing: 10

                Rectangle {
                    border.color: Material.backgroundColor
                    width: circle.itemWidth
                    height: circle.itemHeight

                    TextInput {
                        id: txtEmail
                        anchors.fill: parent
                    }
                }

                Rectangle {
                    border.color: Material.backgroundColor
                    width: circle.itemWidth
                    height: circle.itemHeight

                    TextInput {
                        id: txtPass
                        anchors.fill: parent
                        echoMode: TextInput.Password
                    }
                }

                Rectangle {
                    border.color: Material.backgroundColor
                    width: circle.itemWidth
                    height: circle.itemHeight

                    TextInput {
                        id: txt2FA
                        anchors.fill: parent
                    }
                }
            }
        }

        Button {
            anchors {
                top: row.bottom
                topMargin: 10
                horizontalCenter: row.horizontalCenter
            }

            width: row.width
            text: qsTr("Login")
            onClicked: auth.requestLogin(txtEmail.text, txtPass.text,
                txt2FA.text)
        }
    }
}