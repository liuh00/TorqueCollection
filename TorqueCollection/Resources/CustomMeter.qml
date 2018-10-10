import QtQuick 2.11
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3

Item{
    id: item1
    width: 200
    height: 200

    property real rpm: 0;
    Rectangle{
        width: 400
        height: 400
        color: "#040404"
        anchors.fill: parent
    }


    Rectangle {
        id: rectangle
        color: "#191919"
        height: (item1.width >= item1.height) ? item1.height / 2 : item1.width /2
        width: height
        radius: width /2
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter

        border.width: 0

        Rectangle {
            id: centerLine
            y: 82
            height: 2
            color: "#4e4e4e"
            anchors.rightMargin: 16
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            border.width: 0
            anchors.right: parent.right
            anchors.left: parent.left
        }

        Label {
            id: displayRPM
            y: 68
            height: 26
            color: "#f5f5f5"
            text: rpm.toFixed(0);
            verticalAlignment: Text.AlignVCenter
            anchors.bottom: centerLine.top
            anchors.bottomMargin: 20
            anchors.right: centerLine.right
            anchors.rightMargin: 0
            anchors.left: centerLine.left
            anchors.leftMargin: 0
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 48
        }

        Label {
            id: label1
            x: 70
            height: 26
            color: "#f5f5f5"
            text: qsTr("RPM")
            anchors.top: centerLine.bottom
            anchors.topMargin: 20
            anchors.left: centerLine.left
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
            anchors.right: centerLine.right
            horizontalAlignment: Text.AlignHCenter
            anchors.leftMargin: 0
            font.pixelSize: 24
        }

        Label {
            id: label2
            height: 26
            color: "#f5f5f5"
            text: qsTr("x 1000")
            anchors.left: label1.left
            anchors.rightMargin: 0
            verticalAlignment: Text.AlignVCenter
            anchors.right: label1.right
            horizontalAlignment: Text.AlignHCenter
            anchors.top: label1.bottom
            anchors.leftMargin: 0
            anchors.topMargin: 0
            font.pixelSize: 24
        }

        ArcItem {
            id: arcItem
            asynchronous: true
            strokeColor: "#3eee6b"
            strokeWidth: 4
            anchors.rightMargin: -10
            anchors.leftMargin: -10
            anchors.bottomMargin: -10
            anchors.topMargin: -10
            anchors.fill: parent
            end: 360
        }
    }




    ArcItem {
        id: arcItem1


        height:rectangle.width +100
        width:rectangle.width +100
        anchors.horizontalCenter: rectangle.horizontalCenter
        anchors.verticalCenter: rectangle.verticalCenter
        rotation: 75
        capStyle: 0
        asynchronous: true
        alpha: 180
        begin: 180
        strokeColor: "#191919"
        strokeWidth: 30
        end: 345
    }



    ArcItem {
        id: arcItem2

        asynchronous: true
        strokeWidth: 2
        height: rectangle.width +120
        width:rectangle.width +120
        begin: 180
        rotation: 75
        anchors.horizontalCenter: rectangle.horizontalCenter
        anchors.verticalCenter: rectangle.verticalCenter
        end: 345
    }



    Rectangle {
        id: rectangle1
        x: 358
        y: 550
        width: 8
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle2
        x: 297
        y: 556
        width: 8
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle3
        x: 225
        y: 548
        width: 8
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle4
        x: 162
        y: 521
        width: 9
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle5
        x: 110
        y: 482
        width: 8
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle6
        x: 66
        y: 423
        width: 8
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle7
        x: 42
        y: 361
        width: 8
        height: 7
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle8
        x: 35
        y: 296
        width: 7
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }



    Rectangle {
        id: rectangle9
        x: 45
        y: 225
        width: 8
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }




    Rectangle {
        id: rectangle10
        x: 72
        y: 162
        width: 8
        height: 9
        color: "#ffffff"
        radius: 4
        border.width: 0
    }





    Rectangle {
        id: rectangle11
        x: 113
        y: 110
        width: 8
        height: 8
        color: "#ffffff"
        radius: 4
        border.width: 0
    }





    Rectangle {
        id: rectangle12
        color: "#ffffff"
        radius: 4
        anchors.right: rectangle.right
        anchors.rightMargin: 278
        anchors.left: rectangle.right
        anchors.leftMargin: -286
        anchors.bottom: rectangle.top
        anchors.bottomMargin: 71
        anchors.top: rectangle.bottom
        anchors.topMargin: -379
        border.width: 0
    }




    Label {
        id: label
        color: "#f5f5f5"
        text: qsTr("0")
        anchors.right: parent.right
        anchors.rightMargin: 225
        anchors.left: parent.left
        anchors.leftMargin: 363
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        anchors.top: arcItem2.top
        anchors.topMargin: 545
        font.pixelSize: 24
    }





    Label {
        id: label3
        x: 294
        y: 575
        color: "#f5f5f5"
        text: qsTr("1")
        font.pixelSize: 24
    }





    Label {
        id: label4
        x: 215
        y: 565
        height: 25
        color: "#f5f5f5"
        text: qsTr("2")
        font.pixelSize: 24
    }





    Label {
        id: label5
        x: 146
        y: 536
        color: "#f5f5f5"
        text: qsTr("3")
        font.pixelSize: 24
    }





    Label {
        id: label6
        x: 45
        y: 432
        color: "#f5f5f5"
        text: qsTr("5")
        font.pixelSize: 24
    }





    Label {
        id: label7
        x: 88
        y: 493
        width: 14
        height: 24
        color: "#f5f5f5"
        text: qsTr("4")
        font.pixelSize: 24
    }





    Label {
        id: label8
        x: 17
        y: 358
        color: "#f5f5f5"
        text: qsTr("6")
        font.pixelSize: 24
    }





    Label {
        id: label9
        x: 8
        y: 284
        width: 12
        color: "#f5f5f5"
        text: qsTr("7")
        font.pixelSize: 24
    }





    Label {
        id: label10
        x: 20
        y: 205
        color: "#f5f5f5"
        text: qsTr("8")
        font.pixelSize: 24
    }





    Label {
        id: label11
        x: 50
        y: 140
        width: 10
        color: "#f5f5f5"
        text: qsTr("9")
        font.pixelSize: 24
    }





    Label {
        id: label12
        color: "#f5f5f5"
        text: qsTr("10")
        anchors.right: rectangle.left
        anchors.rightMargin: 41
        anchors.left: rectangle.right
        anchors.leftMargin: -365
        anchors.bottom: rectangle.top
        anchors.bottomMargin: 49
        anchors.top: rectangle.bottom
        anchors.topMargin: -373
        font.pixelSize: 24
    }




    Label {
        id: label13
        color: "#f5f5f5"
        text: qsTr("11")
        anchors.right: rectangle.left
        anchors.rightMargin: -11
        anchors.left: rectangle.right
        anchors.leftMargin: -313
        anchors.bottom: rectangle.top
        anchors.bottomMargin: 87
        anchors.top: rectangle.bottom
        anchors.topMargin: -411
        font.pixelSize: 24
    }








    ArcItem {
        id: arcItem3


        height: rectangle.width +90
        end: 105
        width: rectangle.width +90
        anchors.horizontalCenter: rectangle.horizontalCenter
        anchors.verticalCenter: rectangle.verticalCenter
        begin: 0
        rotation: -105
        alpha: 180
        capStyle: 0
        asynchronous: true
        strokeColor: "#3eee6b"
        strokeWidth: 20
    }



    Item {
        id: item2
        width: 200
        height: 200
        rotation: rpm*0.015
        anchors.horizontalCenter: rectangle.horizontalCenter
        anchors.verticalCenter: rectangle.verticalCenter

        Image {
            id: image
            x: 102
            y: 218
            width: 60
            height: 25
            z: 1
            rotation: -130
            source: "image/assets/rpm_needle_195_65.png"
        }
    }


}
