/* Main.qml
 *
 * author:2019051604044liChengYang
 *
 * date:2023-6-13
 *
 */

//ScrollArea

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id:root
    minimumWidth: 945
    minimumHeight: 540
    visible: true

    title: qsTr("DrawShot")

    property int showAnnotationToolClickTimes: 0

    Rectangle{//工具栏
        id:appToolBar
        width: parent.width
        height: 30
        color: "#e6e5e5"

        RowLayout{//stack one
            id:rowAppToolBar
            spacing: (root.width - 7 * 79) / 12

            ToolButton{
                id:undoActionButton
                action:actions.undoAction
                visible: false
            }

            ToolButton{
                id:redoActionButton
                action:actions.redoAction
                visible: false
            }

            ToolButton{
                id:saveActionButton
                action:actions.saveAction
            }

            ToolButton{
                id:saveasActionButton
                action:actions.saveasAction
            }

            ToolButton{
                id:copyActionButton
                action:actions.copyAction
            }

            ToolButton{
                id:exportsActionButton
                action:actions.exportsAction
            }

            ToolButton{
                id:showAnnotationToolActionButton
                action:actions.showAnnotationToolAction
                onClicked: {
                    if(showAnnotationToolClickTimes == 0){
                        rightContent.visible = false
                        leftContent.width = content.width
                        leftContent.height = content.height - bottomTools.height
                        rowAppToolBar.spacing = (root.width - 7 * 79) / 22
                        leftRec.height = leftContent.height
                        leftRec.width = leftContent.width

                        //redo undo 显示
                        undoActionButton.visible = true
                        redoActionButton.visible = true
                        //左边和底部的工具栏显示
                        leftTools.visible = true
                        bottomTools.visible = true
                        leftContent.x = leftTools.width
                        bottomTools.anchors.bottom = content.anchors.bottom


                        showAnnotationToolClickTimes++;
                    } else {
                        leftContent.x = 0
                        leftContent.width = content.width / 3  * 2
                        leftContent.height = content.height
                        leftRec.width = leftContent.width
                        leftRec.height = leftContent.height / 4 * 3
                        leftRec.anchors.centerIn = leftContent
                        rowAppToolBar.spacing = (root.width - 7 * 79) / 12

                        rightContent.visible = true
                        rightContent.width = content.width / 3
                        rightContent.height = content.height
                        rightContent.x = leftContent.width

                        //redo undo 隐藏
                        undoActionButton.visible = false
                        redoActionButton.visible = false
                        //左边和底部的工具栏隐藏
                        leftTools.visible = false
                        bottomTools.visible = false

                        showAnnotationToolClickTimes--;
                    }
                }
            }

            ToolButton{action:actions.configureAction}

            ToolButton{action:actions.aboutAction}

        }

    }



    Content{
        y:30
        id:content
        height: root.height - appToolBar.height
        border.width: 1
        border.color: "#eaeaea"

        LeftContent{
            border.width: 1
            border.color: "#eaeaea"
            id:leftContent
            width: content.width / 3 * 2
            height: content.height

            Rectangle{
                id:leftRec
                width: leftContent.width
                height: leftContent.height / 4 * 3
                anchors.centerIn: leftContent
                color: "grey"
                Image {
                    id:shotPreview
                    anchors.fill: leftRec
                    source:"qrc:/icons/test.png"
                }
            }
        }

        RightContent{
            border.width: 1
            border.color: "#eaeaea"
            id:rightContent
            x:leftContent.width
            width: parent.width / 3
            height: parent.height
        }

        LeftTools{//左边绘图工具栏
            id:leftTools
            visible: false
            width: 30
            height: content.height
            border.width: 2
            border.color: "#d6d6d6"
        }

        BottomTools{//底部绘图工具栏
            id:bottomTools
            visible: false
            x:leftTools.width
            width: content.width - leftTools.width
            border.width: 3
            border.color: "#d6d6d6"
            anchors.bottom: content.bottom
            height: 30

        }


    }

    Actions {
        id:actions
        aboutAction.onTriggered: dialogs.openAboutDialog()
    }

    Dialogs{
        id:dialogs
    }
}
