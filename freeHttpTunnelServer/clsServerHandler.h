#ifndef SINGLEHANDLER_H
#define SINGLEHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "freeHttpTunnelCommon/clsHttpHelper.h"

class clsServerHandler : public QObject
{
    Q_OBJECT
public:
    clsServerHandler(int _socketdiscriptor,QHostAddress _forwardHost,int _forwardPort, int _id,QObject *_parent = 0);
public:
    void sayGoodBye();
private:
    bool isclientwaiting;
protected:
    QHostAddress forwardHost;
    int forwardPort;
    int id;
    QTcpSocket *internalTcpSocket;
    QTcpSocket *externalTcpSocket;
    void logOutput(QString msg);
    clsHttpHelper internalBuffer;
    clsHttpHelper externalBuffer;
public slots:
    void dataFromInternal();
    void dataFromExternal();

    void internalDiscounnected();
    void externalDiscounnected();
    void slotHandleHttpError(QString msg);
};

#endif // SINGLEHANDLER_H
