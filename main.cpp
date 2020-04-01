#include "mainwindow.h"
#include "Cert.h"
#include "Certlist.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickView>

#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("dotty.su");

    QApplication a(argc, argv);

    CertList *certs = qobject_cast<CertList *>(CertList::init());
//    certs->loadCerts("/home/android/cert.2/rootCA.crt");
    certs->loadCerts("/tmp/22/rootCA.crt");
    qInfo() << certs->rowCount();

//    MainWindow w;
//    w.show();
    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<CertList>("Cert", 1, 0, "CertList", &CertList::init);
    engine.load(QUrl("qrc:/root.qml"));

    return a.exec();
}
