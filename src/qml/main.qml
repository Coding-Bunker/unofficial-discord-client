import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 640
    height: 480
    visible: true
    title: application.name

    Button {
        anchors.centerIn: parent
        width: 100
        height: 100
        onClicked: auth.requestLogin()
        text: "Login..."
    }
}
