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
    }

    //利用四个阴影区域，笼罩未选择区域
    Rectangle{
        id: rect1
        width: selectedImg.width
        height: dragRect.y
        anchors.top: selectedImg.top
        color: "#80000000"
    }
    Rectangle{
        id: rect2
        width: dragRect.x
        height: selectedImg.height-rect1.height-rect4.height
        anchors.top: rect1.bottom
        anchors.bottom: rect4.top
        anchors.left: selectedWin.left

        color: "#80000000"
    }
    Rectangle{
        id: rect3
        width: selectedWin.width-rect2.width-dragRect.width
        height: selectedWin.height-rect1.height-rect4.height
        anchors.top: rect1.bottom
        anchors.bottom: rect4.top
        anchors.right: selectedImg.right

        color: "#80000000"
    }
    Rectangle{
        id: rect4
        width: selectedWin.width
        height: selectedWin.height-rect1.height-dragRect.height
        anchors.bottom: selectedImg.bottom
        color: "#80000000"
    }

    //需要实时跟踪鼠标，用MouseArea
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
            DragHandler{}
        }
    }

}
