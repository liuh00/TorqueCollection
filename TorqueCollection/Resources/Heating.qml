import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

PageBackground{
    id: pageBackground
    title: "Heating"

    GridLayout {
        x: 74
        y: 130
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        columnSpacing: 20
        rowSpacing: 20
        rows: 2
        columns: 2

        GroupBox {
            id: groupBox
            Layout.preferredHeight: 274
            Layout.preferredWidth: 288
            visible: true
            spacing: 5
            contentWidth: 1
            antialiasing: false
            smooth: true
            contentHeight: 1
            font.family: "Tahoma"
            wheelEnabled: true
            clip: false
            title: qsTr("Living Room")



            Label {
                id: label1
                x: 173
                y: 21
                width: 78
                height: 33
                text: qsTr("Actual")
                font.pointSize: 18
            }

            Label {
                id: label
                x: 15
                y: 21
                width: 78
                height: 33
                text: qsTr("Target")
                font.pointSize: 18
            }

            ProgressBar {
                id: progressBar
                x: -26
                y: 144
                width: 160
                value: dial.value
                rotation: -90
            }

            ProgressBar {
                id: progressBar1
                x: 132
                y: 144
                width: 160
                rotation: -90
                value: 0.5
            }

            Dial {
                id: dial
                x: 82
                y: 94
                value: 0
            }




        }

        GroupBox {
            id: groupBox1
            title: qsTr("Living Room")
            Layout.preferredHeight: 274
            spacing: 5
            Label {
                id: label2
                x: 173
                y: 21
                width: 78
                height: 33
                text: qsTr("Actual")
                font.pointSize: 18
            }

            Label {
                id: label3
                x: 15
                y: 21
                width: 78
                height: 33
                text: qsTr("Target")
                font.pointSize: 18
            }

            ProgressBar {
                id: progressBar2
                x: -26
                y: 144
                width: 160
                value: dial1.value
                rotation: -90
            }

            ProgressBar {
                id: progressBar3
                x: 132
                y: 144
                width: 160
                value: 0.5
                rotation: -90
            }

            Dial {
                id: dial1
                x: 82
                y: 94
                value: 0
            }
            contentWidth: 1
            smooth: true
            clip: false
            wheelEnabled: true
            antialiasing: false
            Layout.preferredWidth: 288
            visible: true
            contentHeight: 1
            font.family: "Tahoma"
        }

        GroupBox {
            id: groupBox2
            title: qsTr("Living Room")
            Layout.preferredHeight: 274
            spacing: 5
            Label {
                id: label4
                x: 173
                y: 21
                width: 78
                height: 33
                text: qsTr("Actual")
                font.pointSize: 18
            }

            Label {
                id: label5
                x: 15
                y: 21
                width: 78
                height: 33
                text: qsTr("Target")
                font.pointSize: 18
            }

            ProgressBar {
                id: progressBar4
                x: -26
                y: 144
                width: 160
                value: dial2.value
                rotation: -90
            }

            ProgressBar {
                id: progressBar5
                x: 132
                y: 144
                width: 160
                value: 0.5
                rotation: -90
            }

            Dial {
                id: dial2
                x: 82
                y: 94
                value: 0
            }
            contentWidth: 1
            smooth: true
            clip: false
            wheelEnabled: true
            antialiasing: false
            Layout.preferredWidth: 288
            visible: true
            contentHeight: 1
            font.family: "Tahoma"
        }

        GroupBox {
            id: groupBox3
            title: qsTr("Living Room")
            Layout.preferredHeight: 274
            spacing: 5
            Label {
                id: label6
                x: 173
                y: 21
                width: 78
                height: 33
                text: qsTr("Actual")
                font.pointSize: 18
            }

            Label {
                id: label7
                x: 15
                y: 21
                width: 78
                height: 33
                text: qsTr("Target")
                font.pointSize: 18
            }

            ProgressBar {
                id: progressBar6
                x: -26
                y: 144
                width: 160
                value: dial3.value
                rotation: -90
            }

            ProgressBar {
                id: progressBar7
                x: 132
                y: 144
                width: 160
                value: 0.5
                rotation: -90
            }

            Dial {
                id: dial3
                x: 82
                y: 94
                value: 0
            }
            contentWidth: 1
            smooth: true
            clip: false
            wheelEnabled: true
            antialiasing: false
            Layout.preferredWidth: 288
            visible: true
            contentHeight: 1
            font.family: "Tahoma"
        }
    }

}
