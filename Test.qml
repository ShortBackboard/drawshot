import QtQuick
import QtQuick.Controls
import Gt.Component 1.0


ApplicationWindow {
        width: 640
        height: 480
        visible: true
        title: qsTr("Learn QSG")
        color: "white"

        QSGLine{
            id:qsgline
        }
      MouseArea{
          anchors.fill: parent
          onPressed:(mouse)=> {
              console.log("PRESS: "+mouse.x,mouse.y);
          }

          onPositionChanged: (mouse)=> {
              qsgline.width=mouse.x;
              qsgline.height=mouse.y;
              console.log("ChangwPosition: "+mouse.x,mouse.y);
              update();
          }
      }

//        TapHandler{
//            id:handler
//            onTapped: {
//                qsgline.width=lastX;
//                qsgline.height=lastYlastY;
//                qsgline.update();
//            }

//        }

}
