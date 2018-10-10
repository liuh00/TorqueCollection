import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

PageBackground{
    id: pageBackground
    title: "Security"

    GridLayout {
        x: 97
        y: 120
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        columnSpacing: 20
        rowSpacing: 20
        rows: 2
        columns: 2

        GroupBox {
            id: groupBox
            title: qsTr("Living Room")

            GridLayout {
                rows: 4
                columns: 2

                RadioButton {
                    id: radioButton
                    text: qsTr("Smoke Detector")
                }

                Button {
                    id: button
                    text: qsTr("Test")
                }

                RadioButton {
                    id: radioButton1
                    text: qsTr("Movement Detector")
                }

                Button {
                    id: button1
                    text: qsTr("Test")
                }

                Switch {
                    id: switch1
                    text: qsTr("Window 1")
                }

                Label {
                    id: label
                    text: switch1.checked ? "Open":"Close"
                    font.pointSize: 11
                    font.capitalization: Font.AllUppercase
                    font.family: "Times New Roman"
                }

                Switch {
                    id: switch2
                    text: qsTr("Window 2")
                }

                Label {
                    id: label1
                    text: switch2.checked ? "Open":"Close"
                    font.family: "Times New Roman"
                    font.capitalization: Font.AllUppercase
                    font.pointSize: 11
                }
            }
        }

        GroupBox {
            id: groupBox1
            GridLayout {
                width: 232
                rows: 4
                RadioButton {
                    id: radioButton2
                    width: 142
                    text: qsTr("Smoke Detector")
                }

                Button {
                    id: button2
                    text: qsTr("Test")
                }

                RadioButton {
                    id: radioButton3
                    width: 163
                    text: qsTr("Movement Detector")
                }

                Button {
                    id: button3
                    text: qsTr("Test")
                }

                Switch {
                    id: switch3
                    text: qsTr("Window 1")
                }

                Label {
                    id: label2
                    text: switch3.checked ? "Open":"Close"
                    font.family: "Times New Roman"
                    font.capitalization: Font.AllUppercase
                    font.pointSize: 11
                }

                Switch {
                    id: switch4
                    text: qsTr("Window 2")
                }

                Label {
                    id: label3
                    text: switch4.checked ? "Open":"Close"
                    font.family: "Times New Roman"
                    font.capitalization: Font.AllUppercase
                    font.pointSize: 11
                }
                columns: 2
            }
            title: qsTr("Living Room")
        }

        GroupBox {
            id: groupBox2
            GridLayout {
                width: 232
                rows: 4
                RadioButton {
                    id: radioButton4
                    text: qsTr("Smoke Detector")
                }

                Button {
                    id: button4
                    text: qsTr("Test")
                }

                RadioButton {
                    id: radioButton5
                    text: qsTr("Movement Detector")
                }

                Button {
                    id: button5
                    text: qsTr("Test")
                }

                Switch {
                    id: switch5
                    text: qsTr("Window 1")
                }

                Label {
                    id: label4
                    text: switch5.checked ? "Open":"Close"
                    font.family: "Times New Roman"
                    font.capitalization: Font.AllUppercase
                    font.pointSize: 11
                }

                Switch {
                    id: switch6
                    text: qsTr("Window 2")
                }

                Label {
                    id: label5
                    text: switch6.checked ? "Open":"Close"
                    font.family: "Times New Roman"
                    font.capitalization: Font.AllUppercase
                    font.pointSize: 11
                }
                columns: 2
            }
            title: qsTr("Living Room")
        }

        GroupBox {
            id: groupBox3
            Layout.preferredHeight: 251
            Layout.preferredWidth: 256
            GridLayout {
                width: 232
                rows: 4
                RadioButton {
                    id: radioButton6
                    text: qsTr("Smoke Detector")
                }

                Button {
                    id: button6
                    text: qsTr("Test")
                }

                RadioButton {
                    id: radioButton7
                    text: qsTr("Movement Detector")
                }

                Button {
                    id: button7
                    text: qsTr("Test")
                }

                Switch {
                    id: switch7
                    text: qsTr("Window 1")
                }

                Label {
                    id: label6
                    text: switch7.checked ? "Open":"Close"
                    font.family: "Times New Roman"
                    font.capitalization: Font.AllUppercase
                    font.pointSize: 11
                }

                Switch {
                    id: switch8
                    text: qsTr("Window 2")
                }

                Label {
                    id: label7
                    text: switch8.checked ? "Open":"Close"
                    font.family: "Times New Roman"
                    font.capitalization: Font.AllUppercase
                    font.pointSize: 11
                }
                columns: 2
            }
            title: qsTr("Living Room")
        }
    }

}
