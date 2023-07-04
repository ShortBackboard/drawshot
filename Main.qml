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
import  qml.Component 1.0

ApplicationWindow {
    id:root
    minimumWidth: 945
    minimumHeight: 540
    visible: true

    title: qsTr("DrawShot")

    property alias priImg: shotPreview
    property alias priWin: leftRec
    property alias selectWin: select
    property alias tipBox: hintRec


    property int showAnnotationToolClickTimes: 0
    //    property alias imageMouseAreaControl: imageMouseArea
    property alias imageTapHandlerControl: draghandler

    //启动软件则截取当前全屏
    //开启定时器和动画效果
    Component.onCompleted:{
        hintRecTimer.start()
        animationHint.running = true
        shotFullScreen()
        Func.setPriImgSource()
        hintRecTimer.start()
    }

    //宽度和高度改变时改变Content对应的属性
    onWidthChanged: {
        if(showAnnotationToolClickTimes == 1){//绘图界面
            content.width = root.width
            content.height = root.height - 37

            leftContent.width = content.width - bottomTools.height
            leftContent.height = content.height - bottomTools.height

            leftRec.height = leftContent.height
            leftRec.width = leftContent.width

            bottomTools.width = content.width - leftTools.width
            bottomTools.anchors.bottom = content.bottom
            //更新图像绘画
            painter.update();


        }else if(showAnnotationToolClickTimes == 0){//初始界面
            content.width = root.width
            content.height = root.height - 37

            leftContent.width = content.width - rightContent.width
            leftContent.height = content.height

            leftRec.width = leftContent.width
            leftRec.height = leftContent.height / 4 * 3

            leftRec.anchors.centerIn = leftContent

            rightContent.x = leftContent.width
        }
    }

    onHeightChanged: {
        if(showAnnotationToolClickTimes == 1){//绘图界面
            content.width = root.widsaveActionth
            content.height = root.height - 37



            leftContent.width = content.width - bottomTools.height
            leftContent.height = content.height - bottomTools.height

            leftRec.height = leftContent.height
            leftRec.width = leftContent.width

            bottomTools.width = content.width - leftTools.width
            bottomTools.anchors.bottom = content.bottom



        }else if(showAnnotationToolClickTimes == 0){//初始界面
            content.width = root.width
            content.height = root.height - 37

            leftContent.width = content.width - rightContent.width
            leftContent.height = content.height

            leftRec.width = leftContent.width
            leftRec.height = leftContent.height / 4 * 3

            leftRec.anchors.centerIn = leftContent

            rightContent.x = leftContent.width
        }
    }

    onActiveChanged: setActiveWinId();  //保存活动窗口ID

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
            x: hintRec.width-30
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
            id:animationHint
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
        interval: 5000////3s
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
                onClicked: {
                    painter.undo();
                }
            }

            ToolButton{
                id:redoActionButton
                action:actions.redoAction
                visible: false
                onClicked: {
                    painter.undo();
                }
            }

            ToolButton{
                id:saveActionButton
                action:actions.saveAction
                highlighted: saveActionButton.hovered?true:false
            }

            ToolButton{//另存为
                id:saveasActionButton
                action:actions.saveasAction
                highlighted: saveasActionButton.hovered?true:false
                onClicked: ()=>{
                               dialogs.saveAsFileDialog()
                           }
            }

            ToolButton{//打开本地图片
                id:openActionButton
                action:actions.openAction
                highlighted: openActionButton.hovered?true:false
                onClicked: ()=>{
                               dialogs.openFileDialog()
                           }
            }

            ToolButton{
                id:exportsActionButton//扩展按钮
                action:actions.exportsAction
                highlighted: exportsActionButton.hovered?true:false
                onClicked: menuExport.popup(0,30)//点击显示
                Menu{
                    id:menuExport
                    Menu{
                        title: qsTr("Share")
                        MenuItem{
                            id:qq
                            text: qsTr("Send to QQ")
                            icon.source: "qrc:/icons/qq.png"
                            onTriggered: {
                                share.shareToQQ()
                            }
                            //                            Shortcut {
                            //                                sequence: "Ctrl+Shift+Q"
                            //                                onActivated: qq.triggered()
                            //                            }
                        }

                        MenuItem{
                            id:wexin
                            text: qsTr("Send to WeChat")
                            icon.source: "qrc:/icons/wexin.png"
                            onTriggered: {
                                share.shareToWeXin()
                            }
                        }
                    }

                    Menu{
                        title: qsTr("More")
                        MenuItem{
                            id:recoder
                            text: qsTr("Area Screenrecord")
                            icon.source: "qrc:/icons/record.png"
                            onTriggered: {
                                arearecort.show();
                            }
                        }
                    }
                }

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
//

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
                        shotPreview.fillMode=Image.Stretch;

                        //切换到绘画界面默认放大图片,移动图片的x,y]
                        shotPreview.scale *= 1

                        showAnnotationToolClickTimes++;
                    } else {
                        leftContent.x = 0
                        leftContent.width = content.width / 3  * 2
                        leftContent.height = content.height
//没有意义
//                        leftRec.width = leftContent.width
//                        leftRec.height = leftContent.height

                        leftRec.anchors.centerIn = leftContent
                        rowAppToolBar.spacing = (root.width - 7 * 79) / 12

                        rightContent.visible = true
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
                        shotPreview.fillMode=Image.PreserveAspectFit;
                        //返回主界面恢复默认大小
                        shotPreview.scale = 1

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

    SelectWindow{id: select}

    Content{
        y:37
        id:content
        height: root.height - 37
        border.width: 1
        border.color: "#eaeaea"

        //选择图片
        function selectImage() {
            shotPreview.source = arguments[0]
        }



        LeftContent{
            id:leftContent
            border.width: 1
            border.color: "#eaeaea"
            width: content.width - rightContent.width
            height: content.height
            ScrollView{//可滚动的图片区域
                id:leftRec
                enabled: false //初始界面禁止不可滑动
                clip: false
                anchors.fill: parent
                Image {
                    id:shotPreview
                    anchors.fill: parent
                    source:"qrc:/icons/test.png"
                    focus: false
                    clip: true
                    fillMode:Image.PreserveAspectFit;
                    WheelHandler{//滑轮放大缩小处理
                        id:imageWheel
                        enabled: false //初始界面禁止缩放
                        acceptedModifiers: Qt.ControlModifier //按下controls键才响应滚轮事件
                        property: "scale" //通过按下ctrl键控制
                        onWheel: {
                            console.log("wheel" +painter.width,painter.height);
                            console.log("true"+shotPreview.scale);
                            console.log("true"+painter.changedScale);
                            painter.update();
                        }
                    }
                    DragHandler{//设置可拖拽
                        id: draghandler
                        enabled: false//初始界面禁止拖拽
                    }

                    //设置最大最小缩放
                    onScaleChanged: {
                        if(shotPreview.scale < 0.55){
                            shotPreview.scale = 0.55
                        }

                        if(shotPreview.scale > 8){
                            shotPreview.scale = 8
                        }
                    }

                }
                PaintedItem{
                    property bool textSignal: false
                    id: painter
                    anchors.centerIn: shotPreview

                    width: shotPreview.width*shotPreview.scale
                    height: shotPreview.height*shotPreview.scale

                    pixmapWidthChangeScale:shotPreview.width
                    pixmapHeightChangeScale:shotPreview.height
                    changedScale:1*shotPreview.scale
                    penWidth: bottomTools.fontSizeTool.value
                    penColor: bottomTools.colorTool.color

                    Rectangle {
                        FocusScope {
                            id:textarea
                            width: painter.s_width
                            height: painter.s_height
                            x:painter.s_textPoint.x
                            y:painter.s_textPoint.y
                            visible:painter.textEditStatus;
                            Rectangle {
                                color: "transparent"
                                anchors.fill: parent
                            }
                            TextEdit {
                                id: input
                                anchors.fill: parent
                                anchors.margins: 4
                                text: "ctrl+S保存"
                                focus: true
                                visible: false;
                                color: bottomTools.colorTool.color
                                Keys.onPressed:function(event){
                                    if (event.modifiers == Qt.ControlModifier && event.key == Qt.Key_S)
                                    {
                                        painter.finishGetTextString(0,1,input.text,input.font.pixelSize);
                                        Func.backinputStatusChange();
                                    }
                                }
                            }

                        }

                    }


                }

            }
        }
    }
    RightContent{
        id:rightContent
        border.width: 1
        border.color: "#eaeaea"
        anchors.right: content.right
        width: 315
        height: 500
        onSelectArea: {
            select.winSelected.visible = true;
            select.winSelected.showFullScreen()
        }
    }

    LeftTools{//左边绘图工具栏
        id:leftTools
        visible: false
        width: 40
        height: content.height
        border.width: 2
        border.color: "#d6d6d6"
        //直线
        lineTool.onClicked: {
            painter.currentGraphical=1;    
        }
        //涂鸦
        penTool.onClicked: {
            painter.currentGraphical=2;

        }
        //矩形
        rectTool.onClicked: {
            painter.currentGraphical=3;
        }
        //文本
        textTool.onClicked: {
            Func.inputStatusChange();
        }
        //椭圆
        ellipseTool.onClicked: {
            painter.currentGraphical=5;
        }
        //箭头
        arrowTool.onClicked:
        {
            painter.currentGraphical=6;
        }
        //橡皮擦
        earseTool.onClicked:
        {
            //清除所有数据
            painter.currentGraphical=0;
            painter.clear();
            painter.update();
        }
        mosaicTool.onClicked:
        {
            //涂鸦
            painter.currentGraphical=7;
        }
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
        colorTool.onColorChanged: {
            painter.fontColorChanged(colorTool.color);
        }
        fontSizeTool.onValueChanged: {
            painter.fontSizeChanged(fontSizeTool.value);
        }

        //绑定设置scale和slider
        scaleSliderControl.value : shotPreview.scale / 1 * 100
        scaleSliderControl.onValueChanged: {
            shotPreview.scale = scaleSliderControl.value / 100
        }
    }


    Actions {
        id:actions
        aboutAction.onTriggered: dialogs.openAboutDialog();
        saveAction.onTriggered:
        {
            painter.save();
        }

    }

    Dialogs{
        id:dialogs
        fileOpenDialog.onAccepted: {//打开文件
            content.selectImage(fileOpenDialog.selectedFile)
        }

        fileSaveAsDialog.onAccepted: {//另存为
            console.log(fileSaveAsDialog.selectedFile)
            shotPreview.grabToImage(function(result) { //另外为的图片大小默认和shotPreview大小一致
                    result.saveToFile(fileSaveAsDialog.selectedFile)
                } )
            }
        }
    }
