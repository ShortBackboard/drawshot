//RightContent.qml

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import "Functions.js" as Func

Rectangle{
    signal selectArea();

    color: "#f0f0f0"

    //定时器，用于延时截屏
    Timer{
        id: cutTimer
        interval: 250

        onTriggered: {
            shotFullScreen();
            Func.setPriImgSource();
            root.visible = true;
            tipBox.visible = true;
        }
    }

    ColumnLayout{
        x:0;y:0
        width: parent.width
        height: parent.height

        RowLayout{
            id:row1
            Text {
                font.pointSize: 16
                text: qsTr(" Take a new screenshot")
            }
        }

        ColumnLayout{
            id:row2
            Layout.leftMargin: (parent.width - row2.width) / 2
            spacing: 10
            Button{
                id:rectangularRegionButton
                Layout.preferredWidth:250
                Layout.preferredHeight:30
                text: "Rectangular Region"
                onClicked: {
                    root.visible = false;
                    timer1.start();
                }
                Timer{
                    id: timer1
                    interval: 250
                    onTriggered: {
                        shotFullScreen();
                        selectArea();   //signal
                        Func.setSelectImg();
                    }
                }
            }
            Button{
                id:fullScreenButton
                Layout.preferredWidth:250
                Layout.preferredHeight:30
                text: "Full Screen"
                onClicked: {
                    priImg.source = ""
                    Func.captureScreen(spinBox.value*1000)
                }
            }
            Button{
                id:activeWindowButton
                Layout.preferredWidth:250
                Layout.preferredHeight:30
                text: "Active Window" 
                onClicked: {
                    root.visible = false;
                    timer2.start();
                }
                Timer{
                    id: timer2
                    interval: 250
                    onTriggered: {
                        shotActiveWin();
                        Func.setPriImgSource();
                        root.visible = true;
                    }
                }
            }
            Button{
                id:windowUnderCursorButton
                Layout.preferredWidth:250
                Layout.preferredHeight:30
                text: "Window Under Cursor"
            }
        }

        RowLayout{
            id:row3
            Text {
                font.pointSize: 16
                text: qsTr(" Capture Settings")

            }
        }

        ColumnLayout{
            id:row4
//            Layout.leftMargin: (parent.width - row4.width) / 2


            CheckBox{
                id:checkBox1
                font.pointSize: 12
                text: "Include mouse pointer"
            }
            CheckBox{
                 id:checkBox2
                font.pointSize: 12
                checked: true
                text: "Include window titlebar and borders"
            }
            CheckBox{
                 id:checkBox3
                font.pointSize: 12
                text: "Capture the current pop-up only"
            }
            CheckBox{
                 id:checkBox4
                font.pointSize: 12
                text: "Quit after manual Save or Copy"
            }
            CheckBox{
                 id:checkBox5
                font.pointSize: 12
                text: "Capture on click"
            }
        }

        RowLayout{
            id:row5

            Text {
                font.pointSize: 16
                text: qsTr(" Delay")
            }
            SpinBox{
                id:spinBox
                editable: true
                value: 0
                stepSize: 1
                to:99
            }
        }



    }
}

