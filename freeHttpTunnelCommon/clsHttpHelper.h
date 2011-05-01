#ifndef CLSHTTPHELPER_H
#define CLSHTTPHELPER_H

#include <QObject>

class clsHttpHelper : public QObject
{
    Q_OBJECT
public:
    explicit clsHttpHelper(QObject *parent = 0);

signals:
    void sigError(QString msg);
public slots:

private:
    QByteArray buffer;
    QString generateUrl();
    int state;//0=header not completed yet, 1=header completed
    int  remainingcontenttosend;//:D
    void logOutput(QString msg);
public:
    QByteArray getByRequestHeader(QString domain);
    QByteArray getByResponseHeader();
    QBool hasAny();
    QByteArray getAfterRemoveHeader();
    void clear();
    int append(QByteArray);
};

#endif // CLSHTTPHELPER_H
