#include "Cert.h"

#include <QDir>

// https://stackoverflow.com/questions/16842768/passing-csr-distinguished-name-fields-as-parameters-to-openssl
// https://www.leaderssl.ru/articles/207-vse-pro-openssl-za-5-minut

static bool deleteIfExist(QString fileName) {
    QFile file (fileName);
    if (file.exists())
        return file.remove();

    return true;
}


Cert::Cert(QObject *parent) : QObject(parent) {
    rootDays = 10000;
    certDays = 5000;

    rsa = 2048;
    m_path = "/tmp";
}

void Cert::setPath(QString path) {
    m_path = path;
}

void Cert::setSubj(QString subj)
{
    m_subj = subj;
}

void Cert::setRootCA(QString rootCA)
{
    m_rootCA = m_path + QDir::separator() + rootCA;
}
#include <QDebug>
void Cert::genRootCA(QString rootCA) {
    m_rootCA = m_path + QDir::separator() + rootCA;
    QString fileName = m_path + QDir::separator() + rootCA;

    // delete old files
    deleteIfExist(fileName + ".key");
    deleteIfExist(fileName + ".crt");

    QString cmd;
    cmd += "openssl req -x509 -sha256 -newkey rsa:2048 -keyout " +  fileName + ".key "
           "-out " + fileName + ".crt -days " + QString::number(rootDays) +
           " -nodes -subj '" + m_subj + "'";
    system(cmd.toUtf8());
}

void Cert::genCert(QString cn)
{
    QString fileName = m_path + QDir::separator() + cn;
    QString rootCA = m_rootCA + ".crt";
    QString rootKey = m_rootCA + ".key";

    QString key = fileName + ".key";
    QString csr = fileName + ".csr";
    QString crt = fileName + ".crt";

    // delete old files
    deleteIfExist(fileName + ".key");
    deleteIfExist(fileName + ".csr");
    deleteIfExist(fileName + ".crt");

    // generate key
    QString cmd = "openssl genrsa -out " +
            fileName + ".key " + QString::number(2048);
    qInfo() << "cmd:" << cmd;
    system(cmd.toUtf8());

    // generate csr
    cmd = "openssl req -new -key " + key + " -out " + csr +
          " -subj \""+ m_subj + "/CN=" + cn + "\"";
    qInfo() << "cmd:" << cmd;
    system(cmd.toUtf8());

    // generate crt (signed csr)
    cmd = "openssl x509 -req -in " + csr + " -CA " + rootCA +
          " -CAkey " + rootKey + " -CAcreateserial -out " +
          crt + " -days " + QString::number(certDays);
    qInfo() << "cmd:" << cmd;
    system(cmd.toUtf8());
}
