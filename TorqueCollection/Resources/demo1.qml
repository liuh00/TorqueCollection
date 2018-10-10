import QtQuick 2.11
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3

Item {
    id: item1
    width: 1920
    height: 1080
    property alias item1: item1
    z: 2147483646

    Image {
        id: image
        z: -2
        anchors.fill: parent
        source: "image/assets/backgrounds_195_610.png"
    }




    Image {
        id: image3
        x: 574
        y: 363
        width: 200
        height: 300
        rotation: 0
        source: "image/assets/arc_track_background_195_64.png"
    }

    CustomMeter {
        id: customMeter
        x: 26
        y: 23
    }

    Slider {
        signal rpmChanged(real value);
        id: slider
        x: 652
        y: 468
        to: 11000
        value: 10
        onMoved: {
            rpmChanged(value);
        }
        Component.onCompleted: {
            rpmChanged(value);
        }
    }

    Connections{
        target: slider
        onRpmChanged:{
            customMeter.rpm=value;
        }
    }






}
