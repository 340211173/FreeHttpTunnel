#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QTcpServer>
#include <QHostAddress>

class clsServerDistpacher : public QTcpServer
{
    Q_OBJECT
public:
    explicit clsServerDistpacher(QHostAddress _forwardHost,int _forwardPort, QObject *_parent = 0);

protected:
    void incomingConnection(int socketDescriptor);
private:
    int threadnumber;
    QHostAddress forwardHost;
    int forwardPort;
private slots:
    void eybaba();
};

#endif // DISPATCHER_H
