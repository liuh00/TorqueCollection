import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.2
import QtQuick.VirtualKeyboard 2.3
import QtQuick.VirtualKeyboard.Settings 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Material 2.4
import QtGraphicalEffects 1.0

Pane {
    id: mywindow
    Material.theme: Material.Light

    readonly property int fontSizeExtraSmall: Qt.application.font.pixelSize * 0.8
    readonly property int fontSizeMedium: Qt.application.font.pixelSize * 1.5
    readonly property int fontSizeLarge: Qt.application.font.pixelSize * 2
    readonly property int fontSizeExtraLarge: Qt.application.font.pixelSize * 5


    MouseArea {
        anchors.fill: parent
        Text {
            id: helloText
            text: qsTr("hello Word! View 1")
            font.pixelSize: fontSizeLarge;
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 30
        }

        Button {
            id: openDialog
            text: "OPEN"
            anchors.left: parent.left
            anchors.top: helloText.bottom
            anchors.leftMargin: 30
            anchors.topMargin: 30
            highlighted: true
            Material.background: Material.Blue
            onClicked: {
                fileDialog.open()
            }
        }
        Button {
            id: switchBtn
            checkable: true;
            text: "Switch"
            anchors.left: openDialog.right
            anchors.leftMargin: 30
            anchors.top: helloText.bottom
            anchors.topMargin: 30
            highlighted: true
            Material.background: Material.Blue
            onClicked: {

            }
        }

        Button {
            id: quit
            text: "Quit"
            anchors.left: switchBtn.right
            anchors.leftMargin: 30
            anchors.top: helloText.bottom
            anchors.topMargin: 30
            highlighted: true
            Material.background: Material.Blue
            onClicked: {
                mainWindow.closeApp()
            }
        }

        GlowStatusLed{
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.verticalCenter: parent.verticalCenter;
            active:switchBtn.checked
        }


        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            folder: shortcuts.home
        }
    }
}
