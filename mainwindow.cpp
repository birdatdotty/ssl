#include "mainwindow.h"

#include <QDir>
#include <QDebug>
#include "Cert.h"


// https://www.shellhacks.com/ru/create-csr-openssl-without-prompt-non-interactive/

bool deleteIfExist(QString fileName) {
    QFile file (fileName);
    if (file.exists())
        return file.remove();

    return true;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      editOpenssl(new QLineEdit),
      btnGenRootCA(new QPushButton)
{
    editOpenssl->setText("/usr/bin/openssl");
    btnGenRootCA->setText("Создать RootCA");

    mainLayout.addWidget(editOpenssl);
    mainLayout.addWidget(btnGenRootCA);

    connect(btnGenRootCA,&QPushButton::released,
            this, &MainWindow::btnGenRootCAReleased);


//    myServer_cnf = "[ req ]\n"
//            "default_bits = 2048\n"
//            "default_md = sha256\n"
//            "prompt = no\n"
//            "encrypt_key = no\n"
//            "distinguished_name = dn\n"
//            "req_extensions = req_ext\n\n"

//            "[ dn ]\n"
//            "C = CH\n"
//            "O = OrgName text\n"
//            "CN = foo.example.org\n\n"

//            "[ req_ext ]\n"
//            "subjectAltName = DNS:foo.example.org, DNS:foo2.example.org\n";

    setLayout(&mainLayout);
}

MainWindow::~MainWindow()
{
    delete editOpenssl;
    delete btnGenRootCA;
}

//void MainWindow::genRootCA(QString path, QString /*subj*/, QString rootCA)
//{
//    QString fileName = path + QDir::separator() + rootCA;

//    // delete old files
//    deleteIfExist(fileName + ".key");
//    deleteIfExist(fileName + ".crt");

//    // generate config file
//    QString fileConfName = "myserver.cnf";
//    QFile CAServerCnf(path + QDir::separator() + fileConfName);
//    if (!CAServerCnf.exists()) {
//        if (CAServerCnf.open(QIODevice::WriteOnly))
//            CAServerCnf.write(myServer_cnf.toUtf8());
//        else {
//            // ERROR
//        }
//    }

//    // generate key
//    QString cmd = "openssl genrsa -out " + fileName + ".key 2048";
//    system(cmd.toUtf8());

//    // generate self signed cert
//    cmd = "openssl req -x509 -config " + fileConfName +
//            " -new -key " + fileName + ".key -days 10000 " +
//            "-out " + fileName + ".crt";
//    system(cmd.toUtf8());
//}

//void MainWindow::genCert(QString path, QString subj, QString cn)
//{
//    QString fileName = path + QDir::separator() + cn;

//    // delete old files
//    deleteIfExist(fileName + ".key");
//    deleteIfExist(fileName + ".csr");
//    deleteIfExist(fileName + ".crt");

//    // generate key
//    QString cmd = "openssl genrsa -out " +
//            fileName + ".key 2048";
//    system(cmd.toUtf8());

//    // generate csr
//    cmd = "openssl req -new -key " + fileName + ".key"
//          " -out " + fileName + ".csr" +
//          " -subj \""+ subj + "/CN=" + cn + "\"";
//    system(cmd.toUtf8());

//    // generate crt (signed csr)
//    cmd = "openssl x509 -req -in " + fileName + ".csr -CA /tmp/rootCA.crt -CAkey /tmp/rootCA.key -CAcreateserial -out " + fileName + ".crt -days 5000";
//    system(cmd.toUtf8());
//}


void MainWindow::btnGenRootCAReleased()
{
    Cert cert;
    cert.setPath("/home/android/cert");
    cert.setSubj("/C=RU/O=DottySU");
    cert.genRootCA("rootCA");
    cert.genCert  ("server101.mycloud.local");
}

