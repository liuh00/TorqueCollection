import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.1
import QtQuick.Layouts 1.11

Item {
    id: logPage
    anchors.fill: parent

    signal loginSys(string user, string password)
    property alias userName: textInput.text
    property alias password: textInput1.text
    focus: true
    Keys.enabled: true
    Keys.onPressed: {
        if(event.key === Qt.Key_Enter)
        {
            loginSys(userName, password)
        }
    }




    //用户项
    Item {
        id: userItem
        height: 40
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0

        Label {
            id: label1
            color: "#3a3a3a"
            text: "用户:"
            anchors.verticalCenter: parent.verticalCenter
            wrapMode: Text.NoWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 32
            anchors.left: parent.left
            styleColor: "#3a3a3a"
            font.pixelSize: 16
        }

        TextField {
            id: textInput
            text: qsTr("")
            anchors.right: parent.right
            anchors.rightMargin: 32
            anchors.left: label1.right
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            bottomPadding: 0
            topPadding: 0

            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 16
        }
        Label {
            color: "#3a3a3a"
            text: "请输入用户名."
            anchors.fill: textInput
            styleColor: "#3a3a3a"
            font.pixelSize: 16
            visible: textInput.text.length <= 0
        }
    }

    //密码项
    Item {
        id: passwordItem
        height: 40
        anchors.top: userItem.bottom
        anchors.topMargin: 16
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        Label {
            id: label2
            color: "#3a3a3a"
            text: "密码:"
            anchors.verticalCenter: parent.verticalCenter
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 32
            anchors.left: parent.left
            styleColor: "#3a3a3a"
            font.pixelSize: 16
        }

        TextField {
            id: textInput1
            height: 16
            anchors.right: parent.right
            anchors.rightMargin: 32
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: label2.right
            anchors.leftMargin: 16
            bottomPadding: 0
            topPadding: 0
            horizontalAlignment: Text.AlignLeft
            font.pixelSize: 16
            echoMode: TextInput.Password
        }

        Label {
            color: "#3a3a3a"
            text: "请输入密码."
            anchors.fill: textInput1
            styleColor: "#3a3a3a"
            font.pixelSize: 16
            visible: textInput1.text.length <= 0
        }
    }

    //登录按钮
    Button {
        id: loginBtn
        width: 80
        height: 48
        text: qsTr("登录")
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 130
        icon.height: 24
        icon.width: 24
        icon.source: "image/Login_48px.png"
        onClicked: {
            loginSys(userName, password)
        }
    }
}
