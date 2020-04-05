#include "Cert.h"
#include "Certlist.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickView>

//#include <QSettings>
#include "Cert.h"

#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("dotty.su");


    QApplication a(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<CertList>("Cert", 1, 0, "CertList", &CertList::init);
    engine.load(QUrl("qrc:/root.qml"));

    return a.exec();
}
