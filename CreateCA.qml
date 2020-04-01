import QtQuick 2.0
import QtQuick.Dialogs 1.2

import Qt.labs.platform 1.0

import Cert 1.0

FileDialog {
        id: saveDialog
        title: "Где будет сертификат (RootCA.crt)"
//        folder: shortcuts.home
        nameFilters: [ "Сертификаты (*.crt *.pem)", "All files (*)" ]
        fileMode: FileDialog.SaveFile

        onAccepted: {
            CertList.createCA(file)
        }
        onRejected: {
            fileDialog.close();
        }
}
