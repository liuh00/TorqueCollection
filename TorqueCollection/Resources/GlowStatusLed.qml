import QtQuick 2.11
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.4

Item {
    id: root
    property real itemRadius: 10
    property bool active: false
    property color activeColor: Material.color(Material.Red)
    property color inactiveColor: Material.color(Material.BlueGrey)
    Rectangle {
        id: rectangle
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: root.itemRadius * 2
        height: root.itemRadius * 2
        radius: root.itemRadius
        state: root.active ? "active" : "inactive"
        layer.enabled: true
        layer.effect: Glow {
            id: glow
            samples: 15
            spread: 0.3
            transparentBorder: true
            state: root.active ? "active" : "inactive"
            states: [
                State {
                    name: "active"

                    PropertyChanges {
                        target: glow
                        color: root.activeColor
                    }
                },
                State {
                    name: "inactive"

                    PropertyChanges {
                        target: glow
                        color: root.inactiveColor
                    }
                }
            ]
        }
        states: [
            State {
                name: "active"
                PropertyChanges {
                    target: rectangle
                    color: root.activeColor
                }
            },
            State {
                name: "inactive"
                PropertyChanges {
                    target: rectangle
                    color: root.inactiveColor
                }
            }
        ]
    }
}
