#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QTcpServer>


class clsClientDispatcher : public QTcpServer
{
    Q_OBJECT
public:
    explicit clsClientDispatcher(QHostAddress _forwardHost, int _forwardport, QObject *_parent = 0);

protected:
    void incomingConnection(int _socketDescriptor);
private:
    int handlerNumber;
    QHostAddress forwardHost;
    int forwardPort;
private slots:
    void eybaba();
};

#endif // DISPATCHER_H
