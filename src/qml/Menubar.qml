import QtQuick 2.1
import QtQuick.Controls
import QtQuick.Dialogs

MenuBar {
    id: menu_bar
    Dialog {
        title: "About"
        id: about_diag
        modal: false
        contentItem: Text {
            id: ab
            property string homepage: "https://github.com/Coding-Bunker/unofficial-discord-client"
            anchors.centerIn: parent
            text: "Copyright 2021 Federico Guerinoni and Charlie Lin.<br/>
            Homepage: < a href = \"" + homepage + "\">here</a>"
            onLinkActivated: Qt.openUrlExternally(homepage)
            color: Material.foreground
            font.preferShaping: false
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton // we don't want to eat clicks on the Text
            cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
        }
    }
    Menu {
        title: "File"
        MenuItem {
            text: "Quit"
            //shortcut: StandardKey.Quit
            onTriggered: Qt.quit()
        }
    }
    Menu {
        title: "About"
        MenuItem {
            text: "About this build"
            onTriggered: about_diag.open()
        }
    }
}