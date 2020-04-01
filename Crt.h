#ifndef CRT_H
#define CRT_H

#include <QFileInfo>


class Crt {
    public:
        Crt(QString crt);
        void insertKey(QString key);
        void insertCsr(QString csr);
        QString getName() const;
        QString getPath() const;
        QString getCrt() const;
        QString getKey() const;
        QString getCsr() const;

        static QString getName (QString path);
        static QString withoutExtension(const QString & fileName);
        static QString withoutPath(const QString & fileName);
        static QString getPath(const QString & fileName);

        void info();

    private:
        QString name;
        QString path;
        QString crtFile,
                keyFile,
                csrFile;

};

#endif // CRT_H
