import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

MenuBar {
    id: menu_bar
    Dialog {
        title: "About"
        id: about_diag
        contentItem: Text {
            id: ab
            /* beautify ignore:start */
            readonly property string homepage:
                "https://github.com/Coding-Bunker/unofficial-discord-client"
            /* beautify ignore:end */
            anchors.centerIn: parent
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
    /*Settings{
        id: lololololololol
    }*/

    Menu {
        title: "File"
        MenuBarItem {
            text: "Settings"
            Settings {
                id: lololol
            }

            onTriggered: lololol.sd.open()
        }
        MenuBarItem {
            text: "Quit"
            //shortcut: StandardKey.Quit
            onTriggered: Qt.quit()
        }
    }
    Menu {
        title: "About"
        MenuBarItem {
            text: "About this build"
            onTriggered: about_diag.open()
        }
    }
}