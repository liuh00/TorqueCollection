import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.4
import QtQuick.Layouts 1.0
import QtQuick.Dialogs 1.3


Rectangle{


    property alias title: label.text
    width: 300
    height: 800
    color: "#191919"

    Label {
        id: label
        x: 8
        y: 20
        width: 115
        height: 14
        font.bold: true
        font.pixelSize: 20
        lineHeight: 0.9
    }

    Label {
        id: label1
        x: 48
        y: 79
        width: 50
        height: 25
        color: Material.color(Material.DeepOrange)
        text: qsTr("12:23")
        font.pixelSize: 24
        font.weight: Font.Medium
        lineHeight: 0.9
    }

    Label {
        id: label2
        x: 48
        y: 118
        text: qsTr("Sunday")
        font.pixelSize: 12
    }

    Label {
        id: label3
        x: 48
        y: 157
        width: 50
        height: 25
        color: Material.color(Material.DeepOrange)
        text: qsTr("12 April 2016")
        font.pixelSize: 12
        fontSizeMode: Text.VerticalFit
    }

    Label {
        id: label4
        x: 48
        y: 198
        text: qsTr("Toumshetss")
        font.pixelSize: 12
    }

    Label {
        id: label5
        x: 48
        y: 235
        width: 50
        height: 25
        color: Material.color(Material.DeepOrange)
        text: qsTr("18 Degress")
        font.pixelSize: 24
    }

    Label {
        id: label6
        x: 48
        y: 282
        text: qsTr("Power Consumption")
        font.pixelSize: 12
    }

    ProgressBar {
        id: progressBar
        x: 48
        y: 323
        value: 0.5
    }

    Switch {
        id: switch1
        x: 48
        y: 362
        text: qsTr("Ventilation")
    }

    Slider {
        id: slider
        x: 48
        y: 423
        value: 0.5
    }

    Switch {
        id: switch2
        x: 48
        y: 488
        text: qsTr("Alarm Active")
    }

    RadioButton {
        id: radioButton
        x: 48
        y: 551
        text: qsTr("Active Alert")
    }

    ComboBox {
        id: comboBox
        x: 48
        y: 632
        width: 192
        height: 48
        model: ["Normal","Vacation","Party","Test"]
    }

    Button {
        id: button
        x: 48
        y: 712
        width: 192
        height: 48
        text: qsTr("Configure")
        font.underline: false
        font.strikeout: false
        font.capitalization: Font.Capitalize
        onClicked: {
            dialog.open();
        }

    }
    MessageDialog{
        id:dialog
        title: "May I have your attention,please?"
        function show(caption){
            dialog.text=caption;
            dialog.open();
        }
    }




}
