#include <QDir>
#include <QProcess>

#include "Crt.h"


Crt::Crt(QString crt) {
    crtFile = crt;
    name = getName(crt);
    path = getPath(crt);
}

void Crt::insertKey(QString key) {
    keyFile = key;
}

void Crt::insertCsr(QString csr) {
    csrFile = csr;
}

QString Crt::getName() const {
    return name;
}

QString Crt::getPath() const {
    return path;
}

QString Crt::getCrt() const {
    return crtFile;
}

QString Crt::getKey() const {
    return keyFile;
}

QString Crt::getCsr() const {
    return csrFile;
}

QString Crt::getName(QString path) {
    return withoutPath(withoutExtension(path));
}

QString Crt::withoutExtension(const QString &fileName) {
    return fileName.left(fileName.lastIndexOf("."));
}

QString Crt::withoutPath(const QString &fileName) {
    return QFileInfo(fileName).fileName();
}

QString Crt::getPath(const QString &fileName) {
    QString tmpPath = QFileInfo(fileName).path();
    if (tmpPath.at(0) == '.')
        tmpPath = QDir::currentPath() + QDir::separator() + tmpPath;

    return tmpPath + QDir::separator();
}

QString Crt::getSubj(const QString &fileName)
{
    QProcess proc;
    proc.start("openssl", QStringList() << "x509" << "-subject" << "-noout" << "-in" << fileName);
    proc.waitForFinished(-1);
    QString output(proc.readAllStandardOutput());
    return output;
}

#include <QDebug>
void Crt::info() {
    qInfo() << "name: " + name;
    qInfo() << "path: " + path;
    qInfo() << "crtFile: " + crtFile;
    if (keyFile.size() > 0)
        qInfo() << "keyFile: " + keyFile;
    if (csrFile.size() > 0)
        qInfo() << "csrFile: " + csrFile;
    qInfo() << "-------";

}
