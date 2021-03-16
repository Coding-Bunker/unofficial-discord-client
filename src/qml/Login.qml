import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {

    color: Material.backgroundColor

    Row {
        id: row

        spacing: 10
        anchors.centerIn: parent

        Column {
            spacing: 10

            Text {
                text: qsTr("Email:")
                color: Material.accentColor
            }

            Text {
                text: qsTr("Password:")
                color: Material.accentColor
            }

            Text {
                text: qsTr("2FA code (only if you have):")
                color: Material.accentColor
            }
        }

        Column {
            spacing: 10
            readonly property int itemHeight: 17
            readonly property int itemWidth: 270

            Rectangle {
                width: parent.itemWidth
                height: parent.itemHeight

                TextInput {
                    id: txtEmail

                    anchors.fill: parent
                }
            }

            Rectangle {
                width: parent.itemWidth
                height: parent.itemHeight

                TextInput {
                    id: txtPass

                    anchors.fill: parent
                    echoMode: TextInput.Password
                }
            }

            Rectangle {
                width: parent.itemWidth
                height: parent.itemHeight

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

        id: login

        width: row.width
        text: qsTr("Login")
        onClicked: auth.requestLogin(txtEmail.text, txtPass.text, txt2FA.text)
    }
}
