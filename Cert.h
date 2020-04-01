#ifndef CERT_H
#define CERT_H

#include <QObject>

class Cert : public QObject
{
    Q_OBJECT
public:
    explicit Cert(QObject *parent = nullptr);
    void setPath(QString path);
    void setSubj(QString subj);
    void setRootCA(QString rootCA);

    void genRootCA(QString rootCA);
    void genCert(QString cn);

private:
    QString m_path;
    QString RootCA;
    QString RootKey;

    int rootDays, certDays;
    int rsa;
    QString m_rootCA;
    QString m_subj;

signals:

};

#endif // CERT_H
