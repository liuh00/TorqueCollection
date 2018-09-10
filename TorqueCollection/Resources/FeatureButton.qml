import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Button {
    id: button
    checkable: true
    font.pixelSize: fontSizeExtraSmall
    leftPadding: 4
    rightPadding: 4
    topPadding: 12
    bottomPadding: 12
    implicitWidth: 60
    implicitHeight: 90
    enabled: true
    icon.name: "placeholder"
    icon.width: 44
    icon.height: 44
    display: Button.TextUnderIcon
    MouseArea{
        id:mouse_area;
        anchors.fill: parent
        hoverEnabled:true;
        onClicked: {
            emit: parent.clicked();
        }
    }

    background: Rectangle {
        anchors.fill: parent
        color: mouse_area.containsMouse ? "red" : "green"
    }
}
