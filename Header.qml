import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import QtQuick.Dialogs 1.2

import Cert 1.0

RowLayout {
    FileDialog {
        id: fileDialog
        title: "Выберите корневой сертификат"
        folder: shortcuts.home
        nameFilters: [ "Сертификаты (*.crt *.pem)", "All files (*)" ]

        onAccepted: {
            CertList.loadCerts(fileDialog.fileUrl)
        }
        onRejected: {
            fileDialog.close();
        }
    }

    TextField {
            width: 640
            text: CertList.path
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignLeft
            placeholderText: "Не выбрана директория сертификатов"
    }

    Button {
        text: "open..."
        onReleased: fileDialog.open();
    }

}
