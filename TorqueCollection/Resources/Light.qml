import QtQuick 2.11
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0

PageBackground{
    id: pageBackground
    title: "Lights"

    GridLayout {
        x: 68
        y: 97
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        columnSpacing: 20
        rowSpacing: 20
        rows: 2
        columns: 2

        GroupBox {
            id: groupBox
            Layout.preferredWidth: 300
            title: qsTr("Living Room")

            GridLayout {
                rows: 3
                columns: 2

                Switch {
                    id: switch1
                    text: qsTr("All")
                }

                Slider {
                    id: slider
                    Layout.preferredWidth: 160
                    value: 0.5
                }

                Switch {
                    id: switch2
                    text: qsTr("Central")
                }

                Slider {
                    id: slider1
                    Layout.preferredWidth: 160
                    value: 0.5
                }

                Switch {
                    id: switch3
                    text: qsTr("Corner")
                }

                Slider {
                    id: slider2
                    Layout.preferredWidth: 160
                    value: 0.5
                }
            }
        }

        GroupBox {
            id: groupBox1
            GridLayout {
                rows: 3
                Switch {
                    id: switch4
                    width: 81
                    text: qsTr("All")
                }

                Slider {
                    id: slider3
                    value: 0.5
                    Layout.preferredWidth: 160
                }

                Switch {
                    id: switch5
                    width: 111
                    text: qsTr("Central")
                }

                Slider {
                    id: slider4
                    value: 0.5
                    Layout.preferredWidth: 160
                }

                Switch {
                    id: switch6
                    width: 111
                    text: qsTr("Shower")
                }

                Slider {
                    id: slider5
                    value: 0.5
                    Layout.preferredWidth: 160
                }
                columns: 2
            }
            title: qsTr("Bathroom")
        }

        GroupBox {
            id: groupBox2
            Layout.preferredHeight: 198
            Layout.preferredWidth: 300
            GridLayout {
                rows: 3
                Switch {
                    id: switch7
                    width: 83
                    text: qsTr("All")
                    checkable: true
                }

                Slider {
                    id: slider6
                    value: 0.5
                    Layout.preferredWidth: 160
                }

                Switch {
                    id: switch8
                    width: 111
                    text: qsTr("Central")
                }

                Slider {
                    id: slider7
                    value: 0.5
                    Layout.preferredWidth: 160
                }

                Switch {
                    id: switch9
                    width: 111
                    text: qsTr("Bad")
                }

                Slider {
                    id: slider8
                    value: 0.5
                    Layout.preferredWidth: 160
                }
                columns: 2
            }
            title: qsTr("Bedroom01")
        }

        GroupBox {
            id: groupBox3
            Layout.preferredHeight: 198
            Layout.preferredWidth: 300
            GridLayout {
                rows: 3
                Switch {
                    id: switch10
                    width: 83
                    text: qsTr("All")
                    checkable: true
                }

                Slider {
                    id: slider9
                    value: 0.5
                    Layout.preferredWidth: 160
                }

                Switch {
                    id: switch11
                    width: 111
                    text: qsTr("Central")
                }

                Slider {
                    id: slider10
                    value: 0.5
                    Layout.preferredWidth: 160
                }

                Switch {
                    id: switch12
                    width: 111
                    text: qsTr("Bad")
                }

                Slider {
                    id: slider11
                    value: 0.5
                    Layout.preferredWidth: 160
                }
                columns: 2
            }
            title: qsTr("Bedroom02")
        }
    }

}
