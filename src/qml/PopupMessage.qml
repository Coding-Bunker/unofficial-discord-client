import QtQuick 2.15;
import QtQuick.Controls 2.15;
import QtQuick.Controls.Material 2.15

Popup {
    id: popup;

    property alias message : error_message.text
    property alias title : label.text

    anchors.centerIn: parent
    width: 400;
    height: 200;
    modal: true;
    focus: true;
    closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

    Label {
        id: label
        text: "Error"
        color: Material.accentColor
    }

    Text {
        anchors {
            top: login.bottom
            topMargin: 10
            horizontalCenter: popup.horizontalCenter
        }

        id: error_message
        y: 88
        text: qsTr("message")
        anchors.horizontalCenterOffset: 1
        color: Material.accentColor
    }
}