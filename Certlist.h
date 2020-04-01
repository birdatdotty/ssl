#ifndef CERTLIST_H
#define CERTLIST_H

#include <QAbstractListModel>
#include <QJSValue>

#include "Crt.h"

class QQmlEngine;
class QJSEngine;


class CertList : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY sigPath)

public:
    enum roleType{roleName, rolePath, roleCrt, roleKey, roleCsr};
    explicit CertList(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    static QObject* init(QQmlEngine *engine, QJSEngine *scriptEngine);
    static QObject* init();

    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[roleName] = "name";
        roles[rolePath] = "path";
        roles[roleCrt] = "crt";
        roles[roleKey] = "key";
        roles[roleCsr] = "csr";
        return roles;
    }


public slots:
    Q_INVOKABLE void loadCerts(QString uri);
    Q_INVOKABLE void createCert(QString name);
    Q_INVOKABLE void createCA(QString uri);

private:
    QString path;
    QString caFile;
    QStringList files;
    QStringList fullFiles;
    QList<Crt*> list;

    void setPath(QString newPath);
    QString getPath();
signals:
    void sigPath(QString path);
};

#endif // CERTLIST_H
