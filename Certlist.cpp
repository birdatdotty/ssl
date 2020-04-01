#include "Certlist.h"

#include <QJSValue>
#include <QQmlEngine>

#include <QDebug>


#include "Cert.h"
#include "Crt.h"

CertList::CertList(QObject *parent)
    : QAbstractListModel(parent)
{
    QStringList crtList, keyList, csrList;
    crtList << "/home/android/cert/rootCA.crt" << "rootCA2.crt" << "server101.mycloud.crt";
    keyList << "rootCA.key" << "server101.mycloud.key";
    csrList << "rootCA.csr" << "server101.mycloud.csr";

    qInfo() << __LINE__ << "crtList:" << crtList;
    for (QString crtFile: crtList) {
        QString name = Crt::getName(crtFile);
        Crt* crt = new Crt(crtFile);

        for (QString key: keyList)
        if (Crt::getName(key) == name) {
            crt->insertKey(key);
            break;
        }

        for (QString csr: csrList)
        if (Crt::getName(csr) == name) {
            crt->insertCsr(csr);
            break;
        }

        list.append(crt);
    }
}

QVariant CertList::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int CertList::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return list.size();
}

QVariant CertList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
        case roleName: return list.at(index.row())->getName();
        case roleCrt: return list.at(index.row())->getCrt();
        case roleCsr: return list.at(index.row())->getCsr();
        case roleKey: return list.at(index.row())->getKey();
        case rolePath: return list.at(index.row())->getPath();
    }

    return QVariant();
}


QObject *CertList::init(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return init();
}

QObject* CertList::init() {
    static CertList* obj = new CertList();

    return obj;
}

#include <QDir>
#include <QFileInfo>
#include <QUrl>

void CertList::loadCerts(QString uri)
{
    caFile = QFileInfo(uri).fileName();
    caFile = Crt::getName(caFile);
    QString path = QUrl(uri).path();
    QFileInfo ca (path);
    qInfo() << "info:" << ca.path();
    QString curDir = ca.path();
    qInfo() << "curDir:" << curDir;
    QDir sDir(curDir);

    QStringList files = sDir.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
    qInfo() << "files:" << files;

    QStringList crtList = sDir.entryList(QStringList() << "*.crt");
    QStringList keyList = sDir.entryList(QStringList() << "*.key");
    QStringList csrList = sDir.entryList(QStringList() << "*.csr");

    setPath(path);


    beginResetModel();
    qInfo() << __LINE__ << "crtList:" << crtList;
    list.clear();
    for (QString crtFile: crtList) {
        QString name = Crt::getName(crtFile);
        Crt* crt = new Crt(crtFile);

        for (QString key: keyList)
        if (Crt::getName(key) == name) {
            crt->insertKey(key);
            break;
        }

        for (QString csr: csrList)
        if (Crt::getName(csr) == name) {
            crt->insertCsr(csr);
            break;
        }

        list.append(crt);
    }
    qInfo() << "list.size()" << list.size();
    endResetModel();

}

void CertList::createCert(QString name)
{
    qInfo() << "void CertList::createCert(" + name + ")";
    Cert cert;
    qInfo() << __LINE__ << "path:" << path;
    cert.setPath(path);
    cert.setSubj("/C=RU/O=DottySU");
//    cert.setRootCA("rootCA");
    cert.setRootCA(caFile);

    cert.genCert (name);
    loadCerts(path + QDir::separator() + caFile);
}

void CertList::createCA(QString uri)
{
    qInfo() << "uri:" << uri;
    QString path = QFileInfo(uri).path();
            path = QUrl(path).path();
    QString file = QFileInfo(uri).fileName();
    qInfo() << "file" << file;
    qInfo() << "ddd" << QFileInfo(uri).path();
    qInfo() << "ddd" << QFileInfo(uri).fileName();
//    QString path = QUrl(uri).path();
    qInfo() << "path:" << path;
//    cert.setPath("/home/android/cert");
//    cert.setSubj("/C=RU/O=DottySU");
//    cert.genRootCA("rootCA");

    Cert cert;
    cert.setPath(path);
    cert.setSubj("/C=RU/O=DottySU");
    cert.genRootCA(Crt::getName(file));

    loadCerts(uri);
}

void CertList::setPath(QString newPath) {
    path = Crt::getPath(newPath);
    qInfo() << "sigPath(" + newPath + ")";
    qInfo() << "sigPath(" + path + ")";
    sigPath(path);
    qInfo() << "sigPath(" + path + ")";
}

QString CertList::getPath() {
    return path;
}
