import QtQuick 2.0
import QtQuick.Dialogs 1.2

import Qt.labs.platform 1.0

import Cert 1.0

FileDialog {
    property var pathField
        id: saveDialog
        title: "Где будет сертификат (RootCA.crt)"
//        folder: shortcuts.home
        nameFilters: [ "Сертификаты (*.crt *.pem)", "All files (*)" ]
        fileMode: FileDialog.SaveFile

        onAccepted: {
            pathField.text = file
        }
        onRejected: {
            fileDialog.close();
        }
}
