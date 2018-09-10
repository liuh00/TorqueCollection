import QtQuick 2.11
import QtGraphicalEffects 1.0
Item{
    id:root
    property real itemRadius:10
    property bool active: false
    property color activeColor:"red"
    property color inactiveColor:"green"
Rectangle {

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    width: root.itemRadius*2
    height: root.itemRadius*2
    color: root.active?root.inactiveColor:root.activeColor
    radius: root.itemRadius
     layer.enabled: true
     layer.effect: Glow {
                      samples: 15
                      spread: 0.3
                      color: root.active?root.inactiveColor:root.activeColor
                      transparentBorder: true}
  /*  Glow{
          anchors.fill: parent
          radius: 8
          samples: 17
          spread: 0.5;
          color: "red"
    }*/
}
}
