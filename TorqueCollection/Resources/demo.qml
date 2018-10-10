import QtQuick 2.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.11
Pane{
    id:pane;
    width: 1100
    height: 800;
    padding: 0


    MouseArea{
        id: mouseArea
        anchors.fill: parent;

        StackLayout{
            id:stackView
            anchors.right: parent.right
            anchors.rightMargin: 0

            anchors.bottomMargin: 0
            anchors.left: sideBar.right
            anchors.bottom: tabBar.top
            anchors.top: parent.top
            anchors.leftMargin: 0
            currentIndex:tabBar.currentIndex;

            Heating{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter


            }
            Light{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter


            }





            Security{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter


            }


        }

        SideBar {
            id: sideBar
            title: "Smart Home"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        TabBar{
            id:tabBar
            height: 42
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.left: sideBar.right
            anchors.leftMargin: 0
            currentIndex: stackView.currentItem
            TabButton{
                text: "Lights"

            }

            TabButton{
                text: "Heating"

            }
            TabButton{
                text: "Security"
            }
        }







    }
}
