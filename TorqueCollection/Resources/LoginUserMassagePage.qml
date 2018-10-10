import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11
//登录页面
Item {
    id: massagePage

    anchors.fill: parent


    signal logoutSys();
    signal switchUser();
    property alias actUser: actUserLabel.text
    property alias actGroup: actGroupLabel.text

    Rectangle{
        id: rectangle1
        Material.background: Material.Blue
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.top: parent.top
        anchors.topMargin: 20
        height: 88
        color: Material.color(Material.Blue)
        Label{
            id:label4
            color: "#f5f5f5"
            text: "当前用户:"
            anchors.left: parent.left
            anchors.leftMargin: 8
            anchors.top: parent.top
            anchors.topMargin: 24
            font.pixelSize: 16
        }
        Label{
            id:actUserLabel
            color: "#f5f5f5"
            text: "UserName"
            anchors.left: label4.right
            anchors.leftMargin: 4
            anchors.top: label4.top
            anchors.topMargin: 0
            font.pixelSize: 16
        }

        Label {
            id: label5
            x: 5
            color: "#f5f5f5"
            text: "用户组:"
            anchors.top: label4.bottom
            anchors.topMargin: 8
            anchors.right: label4.right
            anchors.rightMargin: 0
            font.pixelSize: 16
        }

        Label {
            id:actGroupLabel
            color: "#f5f5f5"
            text: "UserGroup"
            anchors.left: actUserLabel.left
            anchors.top: actUserLabel.bottom
            font.pixelSize: 16
            anchors.topMargin: 8
            anchors.leftMargin: 0
        }

        Button {
            id: switchUserBtn
            x: 170

            width: 40
            height: 48
            text: ""
            display: AbstractButton.IconOnly
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 8
            icon.height: 24
            icon.width: 24
            icon.source: "image/Change User_48px.png"
            onClicked: logoutSys();
        }

        Rectangle {
            id: rectangle2
            x: 162
            y: 24
            width: 1
            height: 60
            color: "#ffffff"
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: switchUserBtn.left
            anchors.rightMargin: 4
        }



    }

    //注销按钮

    Button {
        id: logoutBtn
        width: 80
        height: 48
        text: qsTr("注销")
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 130
        icon.height: 24
        icon.width: 24
        icon.source: "image/Lock_48px.png"
        onClicked: {
           logoutSys();
        }
    }

    Button {
        id: switchUserBtn1

        width: 104
        height: 48
        text: "切换用户"
        anchors.top: logoutBtn.top
        anchors.topMargin: 0

        anchors.right: logoutBtn.left
        anchors.rightMargin: 8

        icon.width: 24
        icon.height: 24
        icon.source: "image/Change User_48px.png"
        onClicked: {
            switchUser();
        }
    }



}
