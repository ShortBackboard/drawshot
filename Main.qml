/* Main.qml
 *
 * author:2019051604044liChengYang
 *
 *
 */



import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "Functions.js" as Func

ApplicationWindow {
    id:root
    minimumWidth: 945
    minimumHeight: 540
    visible: true

    title: qsTr("DrawShot")

    property alias priImg: shotPreview
    property alias selectWin: leftRec
    property bool isFullScreen: false

    property int showAnnotationToolClickTimes: 0
    property alias imageMouseAreaControl: imageMouseArea
    property alias imageTapHandlerControl: imageTapHandler


    //启动软件则截取当前全屏
    //开启定时器和动画效果
    Component.onCompleted:{
        hintRecTimer.start()
        animation.running = true
        shotFullScreen()
        Func.setPriImgSource()
    }


    //打开软件自动截图成功提示
    Rectangle{
        id:hintRec
        x:(leftContent.width  - hintRec.width) / 2
        y:appToolBar.height + 20

        width: 550
        height: 45
        color: "#a8c8e5"
        border.color: "#5185db"
        opacity: 0.8 //透明
        z:1


        Image {
            id: hintRecImage
            width: 18
            height: 18
            x:20
            y: hintRecText.y
            source: "qrc:/icons/information.png"

        }

        Text {
            id: hintRecText
            x:hintRecImage.width + 35
            y:(hintRec.height - hintRecText.height) / 2
            text: qsTr("The screenshot has been copied to the clipboard.")
        }

        RoundButton{
            id:hintRecButton
            x:hintRecText.width + hintRecImage.width + 60
            y:hintRecText.y
            width: 20
            height: 20
            text: "\u2713"
            onClicked: {
                hintRec.visible = false
            }
        }


        //消失动画
        PropertyAnimation{
            id:animation
            target: hintRec
            property: "opacity"
            to:0
            duration: 3000
            easing.type: Easing.InCirc
        }

    }

    //提示框计时器
    Timer{
        id:hintRecTimer
        interval: 3000////3s
        running: false
        onTriggered: {
            hintRec.visible = false
        }
    }






    Rectangle{//工具栏
        id:appToolBar
        width: parent.width
        height: 28
        color: "#e6e5e5"

        RowLayout{
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
                highlighted: saveActionButton.hovered?true:false
            }

            ToolButton{
                id:saveasActionButton
                action:actions.saveasAction
                highlighted: saveasActionButton.hovered?true:false
            }

            ToolButton{
                id:copyActionButton
                action:actions.copyAction
                highlighted: copyActionButton.hovered?true:false
            }

            ToolButton{
                id:exportsActionButton
                action:actions.exportsAction
                highlighted: exportsActionButton.hovered?true:false
            }

            ToolButton{
                id:showAnnotationToolActionButton
                action:actions.showAnnotationToolAction
                highlighted: showAnnotationToolActionButton.hovered?true:false
                onClicked: {
                    if(showAnnotationToolClickTimes == 0){
                        rightContent.visible = false
                        leftContent.width = content.width - 50
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

                        showAnnotationToolActionButton.checked = true

                        //设置滑动条以及缩放
                        leftRec.enabled = true
                        imageWheel.enabled = true

                        //切换到绘画界面默认放大图片,移动图片的x,y
                        shotPreview.scale *= 2.5

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

                        showAnnotationToolActionButton.checked = false

                        //设置滑动条以及缩放
                        leftRec.enabled = false
                        imageWheel.enabled = false

                        //返回主界面恢复默认大小
                        shotPreview.scale /= 2.5

                        showAnnotationToolClickTimes--;
                    }
                }
            }

            ToolButton{
                id:configureActionButton
                action:actions.configureAction
                highlighted: configureActionButton.hovered?true:false
            }

            ToolButton{
                id:aboutActionButton
                action:actions.aboutAction
                highlighted: aboutActionButton.hovered?true:false
            }

        }

    }



    Content{
        y:37
        id:content
        height: root.height - 37
        border.width: 1
        border.color: "#eaeaea"

        LeftContent{
            border.width: 1
            border.color: "#eaeaea"
            id:leftContent
            width: content.width - rightContent.width
            height: content.height

            ScrollView{//可滚动的图片区域
                id:leftRec
                width: leftContent.width
                height: leftContent.height / 4 * 3
                anchors.centerIn: leftContent
                enabled: false //初始界面禁止不可滑动


                Image {
                    id:shotPreview
                    width: leftRec.width
                    height: leftRec.height
                    source:"qrc:/icons/test.png"

                    focus: false


                    WheelHandler{//滑轮放大缩小处理
                        id:imageWheel
                        enabled: false //初始界面禁止缩放
                        acceptedModifiers: Qt.ControlModifier //按下controls键才响应滚轮事件
                        property: "scale" //通过按下ctrl键控制
                    }

                    MouseArea{//图片区域鼠标样式的改变
                        id:imageMouseArea
                        anchors.fill: parent

                        //                        HoverHandler{//鼠标悬浮
                        //                            cursorShape :Qt.OpenHandCursor
                        //                        }

                        TapHandler{
                            id:imageTapHandler
                            enabled: false //控制是否可以拖动
                        }


                    }
                }

                //设置滑动条可见性
                ScrollBar.horizontal.policy:showAnnotationToolClickTimes == 0 ? ScrollBar.AlwaysOff : ScrollBar.AlwaysOn
                ScrollBar.vertical.policy: showAnnotationToolClickTimes == 0 ? ScrollBar.AlwaysOff : ScrollBar.AlwaysOn
            }
        }

        RightContent{
            id:rightContent
            border.width: 1
            border.color: "#eaeaea"
            anchors.right: content.right
            width: 315
            height: 500
        }

        LeftTools{//左边绘图工具栏
            id:leftTools
            visible: false
            width: 40
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
            height: 50
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
