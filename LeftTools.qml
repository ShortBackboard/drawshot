//LeftTools.qml

import QtQuick
import QtQuick.Controls

Rectangle{
    color: "#f0f0f0"

    property alias dragTool: dragButton
    property alias penTool: penButton
    property alias earseTool: earseButton
    property alias lineTool: lineButton
    property alias arrowTool: arrowButton
    property alias rectTool: rectButton
    property alias ellipseTool: ellipseButton
    property alias mosaicTool: mosaicButton
    property alias textTool: textButton


    Button{
        id:dragButton
        x:5
        y:5 + 0 * 35
        icon.source: "qrc:/icons/drag.png"
        width: 30
        height: 30
        highlighted: dragButton.hovered?true:false

        //imageMouseAreaControl and imageTapHandlerControl from Main.qml

        onClicked: {
            if(dragButton.checked){
                dragButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
                imageTapHandlerControl.enabled = false

            }else{
                dragButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.OpenHandCursor
                imageTapHandlerControl.enabled = true

                if(penButton.checked||earseButton.checked||lineButton.checked||arrowButton.checked||rectButton.checked||ellipseButton.checked||mosaicButton.checked||textButton.checked){
                    penButton.checked = false
                    earseButton.checked = false
                    lineButton.checked = false
                    arrowButton.checked = false
                    rectButton.checked = false
                    ellipseButton.checked = false
                    mosaicButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:penButton
        x:5
        y:5 + 1 * 35
        icon.source: "qrc:/icons/pen.png"
        width: 30
        height: 30
        highlighted: penButton.hovered?true:false
        onClicked: {
            if(penButton.checked){
                penButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                penButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||earseButton.checked||lineButton.checked||arrowButton.checked||rectButton.checked||ellipseButton.checked||mosaicButton.checked||textButton.checked){
                    dragButton.checked = false
                    earseButton.checked = false
                    lineButton.checked = false
                    arrowButton.checked = false
                    rectButton.checked = false
                    ellipseButton.checked = false
                    mosaicButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:earseButton
        x:5
        y:5 + 2 * 35
        icon.source: "qrc:/icons/clear.png"
        width: 30
        height: 30
        highlighted: earseButton.hovered?true:false
        onClicked: {
            if(earseButton.checked){
                earseButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                earseButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||penButton.checked||lineButton.checked||arrowButton.checked||rectButton.checked||ellipseButton.checked||mosaicButton.checked||textButton.checked){
                    dragButton.checked = false
                    penButton.checked = false
                    lineButton.checked = false
                    arrowButton.checked = false
                    rectButton.checked = false
                    ellipseButton.checked = false
                    mosaicButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:lineButton
        x:5
        y:5 + 3 * 35
        icon.source: "qrc:/icons/line.png"
        width: 30
        height: 30
        highlighted: lineButton.hovered?true:false
        onClicked: {
            if(lineButton.checked){
                lineButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                lineButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||earseButton.checked||penButton.checked||arrowButton.checked||rectButton.checked||ellipseButton.checked||mosaicButton.checked||textButton.checked){
                    dragButton.checked = false
                    earseButton.checked = false
                    penButton.checked = false
                    arrowButton.checked = false
                    rectButton.checked = false
                    ellipseButton.checked = false
                    mosaicButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:arrowButton
        x:5
        y:5 + 4 * 35
        icon.source: "qrc:/icons/arrow.png"
        width: 30
        height: 30
        highlighted: arrowButton.hovered?true:false
        onClicked: {
            if(arrowButton.checked){
                arrowButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                arrowButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||earseButton.checked||lineButton.checked||penButton.checked||rectButton.checked||ellipseButton.checked||mosaicButton.checked||textButton.checked){
                    dragButton.checked = false
                    earseButton.checked = false
                    lineButton.checked = false
                    penButton.checked = false
                    rectButton.checked = false
                    ellipseButton.checked = false
                    mosaicButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:rectButton
        x:5
        y:5 + 5 * 35
        icon.source: "qrc:/icons/rect.png"
        width: 30
        height: 30
        highlighted: rectButton.hovered?true:false
        onClicked: {
            if(rectButton.checked){
                rectButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                rectButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||earseButton.checked||lineButton.checked||arrowButton.checked||penButton.checked||ellipseButton.checked||mosaicButton.checked||textButton.checked){
                    dragButton.checked = false
                    earseButton.checked = false
                    lineButton.checked = false
                    arrowButton.checked = false
                    penButton.checked = false
                    ellipseButton.checked = false
                    mosaicButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:ellipseButton
        x:5
        y:5 + 6 * 35
        icon.source: "qrc:/icons/ellipse.png"
        width: 30
        height: 30
        highlighted: ellipseButton.hovered?true:false
        onClicked: {
            if(ellipseButton.checked){
                ellipseButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                ellipseButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||earseButton.checked||lineButton.checked||arrowButton.checked||rectButton.checked||penButton.checked||mosaicButton.checked||textButton.checked){
                    dragButton.checked = false
                    earseButton.checked = false
                    lineButton.checked = false
                    arrowButton.checked = false
                    rectButton.checked = false
                    penButton.checked = false
                    mosaicButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:mosaicButton
        x:5
        y:5 + 7 * 35
        icon.source: "qrc:/icons/mosaic.png"
        width: 30
        height: 30
        highlighted: mosaicButton.hovered?true:false
        onClicked: {
            if(mosaicButton.checked){
                mosaicButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                mosaicButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||earseButton.checked||lineButton.checked||arrowButton.checked||rectButton.checked||ellipseButton.checked||penButton.checked||textButton.checked){
                    dragButton.checked = false
                    earseButton.checked = false
                    lineButton.checked = false
                    arrowButton.checked = false
                    rectButton.checked = false
                    ellipseButton.checked = false
                    penButton.checked = false
                    textButton.checked = false
                }
            }
        }
    }

    Button{
        id:textButton
        x:5
        y:5 + 8 * 35
        icon.source: "qrc:/icons/text.png"
        width: 30
        height: 30
        highlighted: textButton.hovered?true:false
        onClicked: {
            if(textButton.checked){
                textButton.checked = false
//                imageMouseAreaControl.cursorShape = Qt.ArrowCursor
            }else{
                textButton.checked = true
//                imageMouseAreaControl.cursorShape = Qt.CrossCursor
                imageTapHandlerControl.enabled = false

                if(dragButton.checked||earseButton.checked||lineButton.checked||arrowButton.checked||rectButton.checked||ellipseButton.checked||mosaicButton.checked||penButton.checked){
                    dragButton.checked = false
                    earseButton.checked = false
                    lineButton.checked = false
                    arrowButton.checked = false
                    rectButton.checked = false
                    ellipseButton.checked = false
                    mosaicButton.checked = false
                    penButton.checked = false
                }
            }
        }
    }


}
