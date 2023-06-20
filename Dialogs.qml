//Dialog.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Item{
    property alias aboutDialog: about
    property alias fileOpenDialog: fileOpen
    property alias fileSaveAsDialog: fileSaveAs

    function openAboutDialog()  {about.open()}
    function openFileDialog() { fileOpen.open(); }
    function saveAsFileDialog() { fileSaveAs.open(); }

    MessageDialog{
        id:about
        buttons: MessageDialog.Ok

        title: qsTr("关于")
        text:qsTr("本软件名为绘截图，由黄睿娴，万鹿宽，李成杨共同开发。\n\n\n")
    }

    FileDialog{
        id:fileOpen
        title:qsTr("Open A New Picture")
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)" ]//filter
        fileMode:FileDialog.OpenFile//open
    }

    FileDialog{
        id:fileSaveAs
        title:"SaveAs A Picture"
        nameFilters: [ "Image files (*.png *.jpeg *.jpg)"]
        fileMode:FileDialog.SaveFile
        defaultSuffix: ".png"
    }
}
