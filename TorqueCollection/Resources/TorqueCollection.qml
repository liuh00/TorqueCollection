import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Material 2.4

Pane {

    id: mywindow
    Material.theme: Material.Light
    readonly property int fontSizeExtraSmall: Qt.application.font.pixelSize * 0.8
    readonly property int fontSizeMedium: Qt.application.font.pixelSize * 1.5
    readonly property int fontSizeLarge: Qt.application.font.pixelSize * 2
    readonly property int fontSizeExtraLarge: Qt.application.font.pixelSize * 5
    readonly property int material_icons_md_18: 18
    readonly property int material_icons_md_24: 24
    readonly property int material_icons_md_36: 36
    readonly property int material_icons_md_48: 48

    height: 600
    width: 800
    MouseArea {
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        Label {
            id: helloText
            text: qsTr("hello Word! View")
            font.pixelSize: 30
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
        }

        CustomButton {
            id: openDialog
            text: "OPEN"
            anchors.left: parent.left
            anchors.top: helloText.bottom
            anchors.leftMargin: 30
            anchors.topMargin: 30
            icon.source: "image/Open_48px.png"
            icon.width: material_icons_md_24
            icon.height: material_icons_md_24

            enabled: userManager.logged
            onClicked: {
                fileDialog.x = mywindow.x + (mywindow.width - fileDialog.width) / 2
                fileDialog.y = mywindow.y + (mywindow.height - fileDialog.height) / 2
                fileDialog.open()
            }
        }
        CustomButton {
            id: switchBtn
            checkable: true
            text: "Switch"
            anchors.left: openDialog.right
            anchors.leftMargin: 30
            anchors.top: helloText.bottom
            anchors.topMargin: 30
            icon.source: checked ? "image/Light Off_48px.png" : "image/Light On_48px.png"
            icon.width: material_icons_md_24
            icon.height: material_icons_md_24
            enabled: userManager.logged
            onClicked: {

                numAnimation.running = true
                smootAnimation.running = true
            }
        }

        CustomButton {
            id: switchBtn1
            checkable: true
            text: "Switch"
            anchors.left: switchBtn.right
            anchors.leftMargin: 30
            anchors.top: helloText.bottom
            anchors.topMargin: 30

            icon.source: checked ? "image/Light Off_48px.png" : "image/Light On_48px.png"
            icon.width: material_icons_md_24
            icon.height: material_icons_md_24

            onClicked: {
                rec.anchors.leftMargin = 10
                rec1.anchors.leftMargin = 10
                mydata.add();
            }
        }

        CustomButton {
            id: quit
            text: "Quit"
            anchors.left: switchBtn1.right
            anchors.leftMargin: 30
            anchors.top: helloText.bottom
            anchors.topMargin: 30

            icon.source: "image/Shutdown_48px.png"
            icon.width: material_icons_md_24
            icon.height: material_icons_md_24
        1·1···1111111111
            onClicked: {
                mainWindow.closeApp()
            }
        }

        CustomButton {
            id: loginBtn
            height: 52
            text: "登录"
            anchors.left: quit.right
            anchors.leftMargin: 30
            anchors.top: helloText.bottom
            anchors.topMargin: 30

            icon.source: "image/Name_48px.png"
            icon.width: material_icons_md_24
            icon.height: material_icons_md_24

            onClicked: {
                loginWidget.open()
            }
        }

        Rectangle {
            id: rec
            width: 100
            height: 100
            anchors.top: quit.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            color: Material.color(Material.Red)
        }

        Rectangle {
            id: rec1
            width: 100
            height: 100
            anchors.top: rec.bottom
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            color: Material.color(Material.Green)
        }

        GlowStatusLed {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            activeColor: Material.color(Material.Red)
            active: switchBtn.checked
        }

        NumberAnimation {
            id: numAnimation
            target: rec
            property: "anchors.leftMargin"
            easing.type: Easing.InOutQuad
            from: 10
            to: 1000
            duration: 2000
        }
        NumberAnimation {
            id: smootAnimation
            target: rec1
            property: "anchors.leftMargin"
            from: 10
            to: 1000
            duration: 2000
        }

        FileDialog {
            id: fileDialog
            title: "Please choose a file"
            folder: shortcuts.home
        }

        Login {
            id: loginWidget
            oldLoginUser: userManager.logUser
            actUser: userManager.actUserName
            actGroup: userManager.actUserGroup
            logged: userManager.logged
            onLoginOut: {
                userManager.logout()
            }
            onLogin: {
                userManager.login(user, password)
            }
        }

        CustomLabel {
            id: customLabel
            x: 669
            y: 95
            color: Material.color(Material.Red)
            text:mydata.count
            font.bold: true
            font.pixelSize: 32
        }
    }
}
