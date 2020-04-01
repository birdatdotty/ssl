#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPushButton>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVBoxLayout mainLayout;
    QLineEdit* editOpenssl;
    QPushButton* btnGenRootCA;

//    QString myServer_cnf;

//    void genRootCA(QString path, QString subj, QString rootCA);
//    void genCert(QString path, QString subj, QString cn);

private slots:
    void btnGenRootCAReleased();
};
#endif // MAINWINDOW_H
