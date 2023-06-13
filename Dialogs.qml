//Dialog.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Item{
    property alias aboutDialog: about

    function openAboutDialog()  {about.open()}

    MessageDialog{
        id:about
        buttons: MessageDialog.Ok

        title: qsTr("About DrawShot")
        text:qsTr("本软件为绘截图，由黄睿娴，万鹿宽，李成杨共同开发。\n")
    }
}
