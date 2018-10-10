import QtQuick 2.11
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3
import QtQuick.Extras 1.4
 Pane {
    id: pane
    width: 1000
    height: 800
    font.capitalization: Font.Capitalize
    spacing: -1
    bottomPadding: 0
    topPadding: 0
    rightPadding: 0
    leftPadding: 0
    contentWidth: -2

    ArcItem {
        id: arcItem
        x: 518
        y: 244
        width: 200
        height: 200
        alpha: 360
        begin: 0.2
        end: 360
        rotation: 0
        scale: 1
        strokeWidth: 30
        strokeColor: Material.color(Material.DeepOrger)
    }

    CircularGauge {
        id: circularGauge
        x: 184
        y: 262
    }

 }
