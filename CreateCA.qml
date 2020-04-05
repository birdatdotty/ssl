import QtQuick 2.0
import QtQuick.Dialogs 1.2

import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import Cert 1.0

Dialog {
    title: "Создание сертификата"
    id: root

    standardButtons: StandardButton.Save | StandardButton.Cancel

    SaveCAFile {id: selectPath; pathField: pathField}

    MessageDialog {
        id: emty
        title: "Поле пустое"
        text: "Вы не ввели имя устройсва"
        onAccepted: {
            console.log("And of course you could only agree.")
            emty.close()
        }
    }

    contentItem: Rectangle {
        implicitWidth: 600
        implicitHeight: 100

        GridLayout {
            Text {
                Layout.rowSpan: 1
                Layout.columnSpan: 1

                text: qsTr("Имя файла(полный путь)")
            }
            TextField {
                id: pathField
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.rowSpan: 1
                Layout.columnSpan: 3

                horizontalAlignment: Text.AlignLeft
                placeholderText: "Введите имя устройств (host.domain.local)"
            }
            Button {
                text: ">"
                onClicked: selectPath.open()

            }
            Text {
                Layout.row: 2
                Layout.rowSpan: 1
                Layout.columnSpan: 1

                text: qsTr("Описание(subject)")
            }
            TextField {
                id: subjectField
                Layout.row: 2
                Layout.column: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.rowSpan: 1
                Layout.columnSpan: 2

                horizontalAlignment: Text.AlignLeft
                placeholderText: "/C=RU/O=Any Department/emailAddress=root@example.com"
            }

        }
    }

    onAccepted: CertList.createCA(pathField.text, subjectField.text)
//    onRejected: console.log("Cancel clicked")
}

//FileDialog {
//        id: saveDialog
//        title: "Где будет сертификат (RootCA.crt)"
////        folder: shortcuts.home
//        nameFilters: [ "Сертификаты (*.crt *.pem)", "All files (*)" ]
//        fileMode: FileDialog.SaveFile

//        onAccepted: {
//            CertList.createCA(file)
//        }
//        onRejected: {
//            fileDialog.close();
//        }
//}
