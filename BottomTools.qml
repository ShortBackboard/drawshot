//BottomTools.qml

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Rectangle{
    color: "#f0f0f0"

    property alias scaleSliderControl: slider

    Label{
        id:labelSize
        x:10
        y:14
        text: "Size: "
    }

    SpinBox{
        id:spinBox
        x:10 + labelSize.width
        y:11
        width: 50
        from: 0
        to: 30

    }

    Label{
        id:labelSelect
        x:100 + labelSize.width
        y:14
        text: "Select color: "
    }

    Rectangle{
        id:colorSelect
        x:205 + labelSize.width
        y:9
        height: 30
        width: 50
        color: "#00a5ff"
        TapHandler{
            onTapped: {
                colordialog.open()
//                console.log("colorSelect Tapped")
            }
        }

    }

    ColorDialog {
        id: colordialog
        selectedColor: colorSelect.color
        onAccepted: {
            colorSelect.color = selectedColor
//            console.log(colorSelect.color)
        }
    }


//todo:scale Control
    Rectangle{
        height: parent.height
        width: 300
//        border.color: "red"
        anchors.right: parent.right
        Label{
            id:labelScael
            x:10
            y:14
            text: "Scale: "
        }

        Slider{
            id:slider
            from: 0
            to:800 //最大8倍
//            value: 125
            x:65
            y:17


        }

        Label{
            id:scaleLabel
            x:230
            y:12
            text: slider.value.toFixed() +"%"
            font.pixelSize: 20
        }
    }




}
