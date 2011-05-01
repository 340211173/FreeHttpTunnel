#ifndef CLSHTTPHELPER_H
#define CLSHTTPHELPER_H

#include <QObject>

class clsHttpHelper : public QObject
{
    Q_OBJECT
public:
    explicit clsHttpHelper(QObject *parent = 0);

signals:

public slots:

private:
QByteArray buffer;
    QString generateUrl();
public:
    QByteArray getByRequestHeader(QString domain);
    QByteArray getByResponseHeader();
    QBool hasAny();
    QByteArray getAfterRemoveHeader();
    void clear();
    int append(QByteArray);
};

#endif // CLSHTTPHELPER_H
