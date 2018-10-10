import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11

Dialog {
    id: dialog
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    width: 300
    height: 280
    font.pointSize: 0
    padding: 1
    header.visible: false
    modal: true
    Material.theme: Material.Light
    property string oldLoginUser
    property string actUser
    property string actGroup
    property bool logged

    signal loginOut
    signal login(string user, string password)
    Item {
        id: headerItem
        height: 48

        anchors.top: parent.top
        anchors.topMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Image {
            id: image
            width: 48
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 32
            source: "image/Maintenance_48px.png"
        }

        Label {
            id: label
            color: "#3a3a3a"
            text: "用户登录"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: image.right
            anchors.leftMargin: 16
            font.pixelSize: 16
            styleColor: "#3a3a3a"
        }

        Rectangle {
            id: rectangle
            height: 1
            color: "#00000000"
            border.width: 3
            border.color: Material.color(Material.Grey)
            anchors.rightMargin: 16
            anchors.leftMargin: 16
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.left: parent.left
        }
    }

    StackLayout {
        id: stackView
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: headerItem.bottom
        anchors.topMargin: 0

        currentIndex: logged ? 0:1

        LoginUserMassagePage {
            id:loginMassage
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            actUser: dialog.actUser
            actGroup: dialog.actGroup
            onLogoutSys: {
                loginOut()
                loginPage.password = ""
            }

            onSwitchUser: {
                loginOut()
                loginPage.password = ""
            }
        }
        LoginUserPage {
            id: loginPage
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            onLoginSys: {
                login(user, password)
                loginPage.password = ""
            }
            Component.onCompleted: {
                loginPage.userName = dialog.oldLoginUser
            }
        }
    }

    Button {
        id: button
        width: 28
        height: 28
        padding: 0
        rightPadding: 0
        leftPadding: 0
        bottomPadding: 0
        topPadding: 0
        display: AbstractButton.IconOnly
        anchors.top: parent.top
        anchors.topMargin: -12
        anchors.right: parent.right
        anchors.rightMargin: 1
        background: Image {

            source: "image/Close Window_48px.png"
            anchors.fill: parent
        }
        onClicked: {
            loginPage.password = ""
            dialog.reject()
        }
    }
}
