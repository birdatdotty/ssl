import QtQuick 2.0
import QtQuick.Controls 2.12

import Qt.labs.platform 1.0
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

import Cert 1.0

Dialog {
    title: "Создание сертификата"
    id: root

    standardButtons: StandardButton.Save | StandardButton.Cancel

    function end() {
        textField.clear()
        root.close()
    }

    function start() {
        if (textField.text === '')
            emty.open()
        else {
            CertList.createCert(textField.text)

            root.end();
        }
    }


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
            rows: 1
            columns: 3
            anchors.fill: parent
            TextField {
                id: textField
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.rowSpan: 1
                Layout.columnSpan: 3

                horizontalAlignment: Text.AlignLeft
                placeholderText: "Введите имя устройств (host.domain.local)"
            }
//            Button {
//                Layout.fillWidth: true
//                Layout.fillHeight: true
//                Layout.rowSpan: 1
//                Layout.columnSpan: 2

//                text: "Создать"
//                onReleased: root.start()
//            }
//            Button {
//                Layout.fillHeight: true
//                Layout.rowSpan: 1
//                Layout.columnSpan: 1

//                text: "Отменить"
//                onReleased: root.end()
//            }

        }

    }
    onAccepted: root.start()
}
