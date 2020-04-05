#include "Certlist.h"

#include <QJSValue>
#include <QQmlEngine>

#include <QSettings>

#include <QDebug>


#include "Cert.h"
#include "Crt.h"

CertList::CertList(QObject *parent)
    : QAbstractListModel(parent)
{
//    QSettings settings( "openSslRootCA.conf", QSettings::IniFormat, this );
    qInfo() << "CertList::CertList(QObject *parent)";
    QSettings settings( this );

    settings.beginGroup( "main" );
    QVariant certPath = settings.value("cert" );
    settings.endGroup();


    qInfo() << __LINE__ << certPath;
    if (certPath.isValid())
        loadCertsPath(certPath.toString());

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
    qInfo() << "QObject *CertList::init(QQmlEngine *engine, QJSEngine *scriptEngine)";
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return init();
}

QObject* CertList::init() {
    qInfo() << "QObject* CertList::init()";
    static CertList* obj = new CertList();

    return obj;
}

#include <QDir>
#include <QFileInfo>
#include <QUrl>

void CertList::loadCerts(QString uri)
{
    qInfo() << __LINE__ << "void CertList::loadCerts(QString uri)" << uri;
    QString path = QUrl(uri).path();

    loadCertsPath(path);
}

void CertList::createCert(QString name)
{
    qInfo() << "void CertList::createCert(QString name):" << name;
    Cert cert;
    qInfo() << __LINE__ << "path:" << path;
    cert.setPath(path);
//    cert.setSubj(subj);
    cert.setSubj(subj);
//    cert.setRootCA("rootCA");
    cert.setRootCA(caFile);

    cert.genCert (name);
    loadCerts(caFile);
}

void CertList::createCA(QString uri, QString subject)
{
//    qInfo() << "void CertList::createCA(QString uri):" << uri;
//    QString path = QFileInfo(uri).path();
//            path = QUrl(path).path();
//    QString file = QFileInfo(uri).fileName();


//    loadCerts(uri);
//    qInfo() << "uri:" << uri;
    QString path = QFileInfo(uri).path();
    path = QUrl(path).path();
    QString file = QFileInfo(uri).fileName();

    Cert cert;
    cert.setPath(path);
    cert.setSubj(subject);
    cert.genRootCA(Crt::getName(file));

    loadCerts(uri);

}

void CertList::setPath(QString newPath) {
    qInfo() << "void CertList::setPath(QString newPath)";
    path = Crt::getPath(newPath);
    sigPath(path);
}

void CertList::loadCertsPath(QString path)
{
    qInfo() << "void CertList::loadCertsPath(QString path):" << path;
    caFile = path;
    caKey = Crt::getPath(caFile) + Crt::getName(caFile) + ".key";

    qInfo() << "caFile:" << caFile;
    qInfo() << "caKey:" << caKey;

    saveCertsPath(path);
    Cert cert;
    cert.setPath(path);
    subj = Cert::normalizeSubj( Crt::getSubj(path) );

    QFileInfo ca (path);
    QString curDir = ca.path();
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

void CertList::saveCertsPath(QString path)
{
    qInfo() << "void CertList::saveCertsPath(QString path)" << path;
    QSettings settings( this );
    settings.beginGroup( "main" );
    settings.setValue( "cert", path );
    settings.endGroup();

    settings.sync();
}

QString CertList::getPath() {
    qInfo() << "QString CertList::getPath()";
    return path;
}
