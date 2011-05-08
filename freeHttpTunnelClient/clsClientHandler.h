#ifndef SINGLEHANDLER_H
#define SINGLEHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include "freeHttpTunnelCommon/clsHttpHelper.h"

class clsClientHandler : public QObject
{
    Q_OBJECT
public:
    explicit clsClientHandler(int _socketdiscriptor,QHostAddress _forwardHost,int _forwardPort,int _id,QObject *parent = 0);
public:
    void sayGoodBye();
private:
    int id;

    void logOutput(QString msg);

    QTcpSocket *internalTcpSocket;
    QTcpSocket *externalTcpSocket;
    //    QByteArray internalBuffer;
    clsHttpHelper internalBuffer;
    //    QByteArray externalBuffer;
    clsHttpHelper externalBuffer;
    QHostAddress forwardHost;
    int forwardPort;
    bool isPreRequestFinished;
public slots:
    void dataFromInternal();
    void dataFromExternal();

    void internalDiscounnected();
    void externalDiscounnected();
    void slotErrorHandler(QString message);
    //    void slotErrorHttpHandler(QString message);
    void slotGetRestOfIceCream();
signals:
    void someError(QString message);
};

#endif // SINGLEHANDLER_H
