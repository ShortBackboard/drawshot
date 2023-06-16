//LeftTools.qml

import QtQuick
import QtQuick.Controls

Rectangle{
    color: "#f0f0f0"

    Button{
        id:penButton
        x:5
        y:5
        icon.source: "qrc:/icons/pen.png"
        width: 30
        height: 30
        highlighted: penButton.hovered?true:false
        onClicked: {
            if(penButton.checked){
                penButton.checked = false
            }else{
                penButton.checked = true
            }
        }
    }

    Button{
        id:paintButton
        x:5
        y:5 + 1 * 35
        icon.source: "qrc:/icons/paint.png"
        width: 30
        height: 30
        highlighted: paintButton.hovered?true:false
        onClicked: {
            if(paintButton.checked){
                paintButton.checked = false
            }else{
                paintButton.checked = true
            }
        }
    }

    Button{
        id:lineButton
        x:5
        y:5 + 2 * 35
        icon.source: "qrc:/icons/line.png"
        width: 30
        height: 30
        highlighted: lineButton.hovered?true:false
        onClicked: {
            if(lineButton.checked){
                lineButton.checked = false
            }else{
                lineButton.checked = true
            }
        }
    }

    Button{
        id:arrowButton
        x:5
        y:5 + 3 * 35
        icon.source: "qrc:/icons/arrow.png"
        width: 30
        height: 30
        highlighted: arrowButton.hovered?true:false
        onClicked: {
            if(arrowButton.checked){
                arrowButton.checked = false
            }else{
                arrowButton.checked = true
            }
        }
    }

    Button{
        id:rectButton
        x:5
        y:5 + 4 * 35
        icon.source: "qrc:/icons/rect.png"
        width: 30
        height: 30
        highlighted: rectButton.hovered?true:false
        onClicked: {
            if(rectButton.checked){
                rectButton.checked = false
            }else{
                rectButton.checked = true
            }
        }
    }

    Button{
        id:ellipseButton
        x:5
        y:5 + 5 * 35
        icon.source: "qrc:/icons/ellipse.png"
        width: 30
        height: 30
        highlighted: ellipseButton.hovered?true:false
        onClicked: {
            if(ellipseButton.checked){
                ellipseButton.checked = false
            }else{
                ellipseButton.checked = true
            }
        }
    }

    Button{
        id:mosaicButton
        x:5
        y:5 + 6 * 35
        icon.source: "qrc:/icons/mosaic.png"
        width: 30
        height: 30
        highlighted: mosaicButton.hovered?true:false
        onClicked: {
            if(mosaicButton.checked){
                mosaicButton.checked = false
            }else{
                mosaicButton.checked = true
            }
        }
    }

    Button{
        id:textButton
        x:5
        y:5 + 7 * 35
        icon.source: "qrc:/icons/text.png"
        width: 30
        height: 30
        highlighted: textButton.hovered?true:false
        onClicked: {
            if(textButton.checked){
                textButton.checked = false
            }else{
                textButton.checked = true
            }
        }
    }


}
