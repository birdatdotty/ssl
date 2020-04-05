#ifndef CERT_H
#define CERT_H

// https://www.shellhacks.com/ru/create-csr-openssl-without-prompt-non-interactive/

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

    static QString getSubj(const QString fileName);
    static QString normalizeSubj(QString subj);

private:
    QString m_path;
    QString m_rootCA;
    QString m_rootKey;
    QString m_subj;

    QString RootCA;
    QString RootKey;

    int rootDays, certDays;
    int rsa;

};

#endif // CERT_H
