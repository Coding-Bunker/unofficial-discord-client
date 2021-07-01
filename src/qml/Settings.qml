import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Dialogs
import QtQuick.Window
import Qt.labs.qmlmodels

Dialog {
    id: settings_diag
    property alias sd: settings_diag
    title: "Settings"
    standardButtons: Dialog.Save
    onAccepted: {
        hmi.saveSettings();
        settings_diag.close();
    }

    Text {
        id: title

        text: qsTr("Settings")
        anchors {
            horizontalCenter: parent.horizontalCenter
            topMargin: 10
            top: parent.top
        }

        color: Material.foreground
        font.bold: true
        font.pixelSize: 24
    }

    ListView {
        id: lw

        anchors {
            top: title.bottom
            bottom: okButton.top
        }

        model: settingsModel

        delegate: DelegateChooser {
            id: chooser

            role: "typeRole"

            DelegateChoice {
                roleValue: 0

                Row {
                    readonly property int listIdx: index
                    spacing: 5

                    Text {
                        text: descriptionRole
                        color: Material.foreground
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    ComboBox {
                        model: choicesRole
                        anchors.verticalCenter: parent.verticalCenter
                        currentIndex: startValueRole
                        onActivated: settingsModel.setParameter(
                            parent.listIdx, index)
                    }
                }
            }
        }
    }
}
