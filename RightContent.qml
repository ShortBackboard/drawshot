//RightContent.qml

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Rectangle{
    color: "#f0f0f0"

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
            }
            Button{
                id:fullScreenButton
                Layout.preferredWidth:250
                Layout.preferredHeight:30
                text: "Full Screen"
            }
            Button{
                id:activeWindowButton
                Layout.preferredWidth:250
                Layout.preferredHeight:30
                text: "Active Window"
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
            }
        }



    }



    //    Button
    //    CheckBox
}

