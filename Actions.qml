//Actions.qml

import QtQuick
import QtQuick.Controls

Item {
    property alias saveAction: save
    property alias saveasAction: saveAs
    property alias openAction: open
    property alias exportsAction: exports
    property alias showAnnotationToolAction: showAnnotationTool
    property alias configureAction: configure
    property alias aboutAction: about
    property alias redoAction: redo
    property alias undoAction: undo

    Action{
        id:save
        text:qsTr("Save")
        icon.source: "qrc:/icons/save.png"
    }

    Action{
        id:saveAs
        text:qsTr("Save As")
        icon.source: "qrc:/icons/saveas.png"
    }

    Action{
        id:open
        text:qsTr("Open")
        icon.source: "qrc:/icons/copy.png"
    }

    Action{
        id:exports
        text:qsTr("Export")
        icon.source: "qrc:/icons/export.png"
    }

    Action{
        id:showAnnotationTool
        text:qsTr("Show Annotation Tools")
        icon.source: "qrc:/icons/showAnnotationsTools.png"
    }

    Action{
        id:configure
        text:qsTr("Configure")
        icon.name: "preferences-system"
    }

    Action{
        id:about
        text:qsTr("About")
        icon.name: "help-about"
    }

    Action{
        id:redo
        icon.name: "edit-redo"
    }

    Action{
        id:undo
        icon.name: "edit-undo"
    }

}
