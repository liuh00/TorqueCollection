import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.4
Rectangle{
    id: rectangle1

    width: 800
    height: 800
    color: "#191919"
    visible: true
    clip: true
    property alias title: label.text

    Label {
        id: label
        x: 8
        y: 20
        width: 115
        height: 14
        font.bold: true
        font.pixelSize: 20
        lineHeight: 0.9
        renderType: Text.NativeRendering
    }

    Rectangle {
        id: rectangle
        x: 532
        width: 400
        height: 200
        color: "#3a3a3a"
        anchors.right: parent.right
        anchors.rightMargin: -130
        anchors.top: parent.top
        anchors.topMargin: -32
        clip: true
        rotation: 45
        border.width: 0
    }
}
