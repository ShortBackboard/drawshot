/*
 * 显示备选截图
 * author: wanlukuan
 * date: 2023-6-15
 */

import QtQuick
import QtQuick.Controls
import "Functions.js" as Func

Window {
    property alias winSelected: selectedWin
    property alias sImg: selectedImg

    id: selectedWin
    visible: false
    Image{
        id: selectedImg
        anchors.fill: parent
//        source: ""
    }

    MouseArea{
        id: mouseArea
        anchors.fill: parent
        drag.target: dragRect

        property int startX: 0
        property int startY: 0
        property int endX: 0
        property int endY: 0

        onPressed: (mouse)=>{
                       startX = mouse.x
                       startY = mouse.y
                       dragRect.width = 0
                       dragRect.height = 0
                       dragRect.visible = true
                   }

        onPositionChanged:
            (mouse)=>{
                endX = mouse.x
                endY = mouse.y
                dragRect.width = Math.abs(endX-startX)
                dragRect.height = Math.abs(endY-startY)
                dragRect.x = startX<endX? startX : endX
                dragRect.y = startY<endY? startY : endY
            }

        Rectangle{
            id: dragRect
            color: "transparent"
            border.color: "royalblue"
            border.width: 1
            visible: false

            TapHandler{
                onDoubleTapped: {
                    Func.cutArea(dragRect.x,dragRect.y,dragRect.width,dragRect.height);
                    dragRect.visible = false;
                    selectedWin.close();
                    root.visible = true;
                }
            }
        }


    }

}
