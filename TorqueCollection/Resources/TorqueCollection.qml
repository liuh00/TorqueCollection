import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 2.2
import QtQuick.VirtualKeyboard 2.3
import QtQuick.VirtualKeyboard.Settings 2.2
import QtQuick.Dialogs 1.2


 Rectangle {
    id: window
	objectName:"window"
    visible: true
    width: 640
    height: 480
    BusyIndicator {
        id: busy
        running: false
        anchors.centerIn: parent
        z: 2
    }
 
    Text {
        id: stateLabel
        font.bold: true
        font.pointSize: 30
        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        z: 3
    }

    Image {
        id: imegeViewer
        asynchronous: true
        cache: false
        anchors.fill: parent
        fillMode: Image.PreserveAspectFit
        onStatusChanged: {
            if (imegeViewer.status == Image.Loading) {
                busy.running = true
                stateLabel.visible = false
            }
            if (imegeViewer.status == Image.Ready) {
                busy.running = false
            }
            if (imegeViewer.status == Image.Error) {
                busy.running = false
                stateLabel.visible = ture
                stateLabel.text = "错误"
            }
        }
    }

    Text {
        id: imagePath
        anchors.left: openFile.right
        anchors.leftMargin: 8
        anchors.verticalCenter: openFile.verticalCenter
        font.pixelSize: 18
    }

    Button {
        id: openFile
        text: "OPEN"
        font.wordSpacing: 0
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30
        onClicked: {
            fileDialog.open()
        }
    }

    Button {
        text: "退出"
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 20
        onClicked: Qt.quit()
    }

		FileDialog {
			id: fileDialog
			title: "Open file."
			nameFilters: ["Image Files (*.jpg *.png *.gif)"]
			onAccepted: {
				imegeViewer.source = fileDialog.fileUrl
				var imageFile = new String(fileDialog.fileUrl)
				imagePath.text = imageFile.slice(8)
			}
		}
}
