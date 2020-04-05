import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.2

import Cert 1.0

ApplicationWindow {
    id: root1
    width: 640
    height: 480
//    color: "#272822"
    visible: true

    NewCert {
        onAccepted: visible = false
        id: msg
    }
    CreateCA {
        onAccepted: visible = false
        id: createCA
    }

    header:  Header{}

    ColumnLayout {
        anchors.fill: parent;

        RowLayout {
            Text {
                text: "Список сертификатов"
            }
        }

        RowLayout {
            id: name
            ListView {
                Layout.alignment: Qt.AlignTop
                Layout.fillWidth: true
                Layout.fillHeight: true

                model: CertList
                delegate: Text {
                    text: index + 1 + "/" + CertList.rowCount() + ": " + name
                }
            }
        }


    }
    onBeforeRendering: {
//        msg.visible = true
//        msg.open();
    }
    footer: RowLayout {
        Button {
            Layout.fillWidth: true
            text: "Добавить сертификат"
            onClicked: msg.visible = true
        }
        Button {
            text: "CREATE CA"
            onClicked: createCA.visible = true
        }
    }
}
