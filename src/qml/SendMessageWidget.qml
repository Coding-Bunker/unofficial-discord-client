import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15

Rectangle {
    color: Material.backgroundColor
    height: parent.height * 0.02
    width: parent.width

    border.color: Material.primary

    Row {
        anchors.fill: parent

        spacing: 5

        TextInput {
            id: txtInput

            height: parent.height
            width: parent.width * .9
            color: Material.foreground
        }

        Button {
            height: parent.height - 2
            width: parent.width * .1
            anchors.verticalCenter: parent.verticalCenter

            background: Rectangle {
                color: "pink"
                anchors.fill: parent
            }

            Text {
                anchors.centerIn: parent
                text: qsTr("send")
            }

            onClicked: {
                hmi.guildsModel.channelsModel.sendMsg(txtInput.text)
                txtInput.clear()
            }
        }
    }
}