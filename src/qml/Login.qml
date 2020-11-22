import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    visible: !user.logged

    height: parent.height / 2
    width: height
    radius: height / 2

    border.color: "black"

    readonly property int itemHeight: 17
    readonly property int itemWidth: 250

    Row {
        id: row
        spacing: 10
        anchors.centerIn: parent

        Column {
            spacing: 10

            Text {
                font.pixelSize: 14
                text: qsTr("Email:")
            }

            Text {
                font.pixelSize: 14
                text: qsTr("Password:")
            }

            Text {
                font.pixelSize: 14
                text: qsTr("2FA code (only if you have):")
            }
        }

        Column {
            spacing: 10

            Rectangle {
                border.color: "black"
                width: itemWidth
                height: itemHeight

                TextInput {
                    id: txtEmail
                    anchors.fill: parent
                    font.pixelSize: 14
                }
            }

            Rectangle {
                border.color: "black"
                width: itemWidth
                height: itemHeight

                TextInput {
                    id: txtPass
                    anchors.fill: parent
                    font.pixelSize: 14
                    echoMode: TextInput.Password
                }
            }

            Rectangle {
                border.color: "black"
                width: itemWidth
                height: itemHeight

                TextInput {
                    id: txt2FA
                    anchors.fill: parent
                    font.pixelSize: 14
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
        onClicked: auth.requestLogin(txtEmail.text, txtPass.text, txt2FA.text)
    }
}
