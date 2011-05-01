#ifndef SINGLEHANDLER_H
#define SINGLEHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include "stuConnectionConfig.h"
#include "freeHttpTunnelCommon/clsHttpHelper.h"

class singlehandler : public QObject
{
    Q_OBJECT
public:
    explicit singlehandler(int socketdiscriptor,int id,stucConneectionConfig connectionconfig,QObject *parent = 0);
    void run();
public:
    void sayGoodBye();
private:
    int id;
    stucConneectionConfig connectionconfig;
    void logOutput(QString msg);

    QTcpSocket *internalTcpSocket;
    QTcpSocket *externalTcpSocket;
//    QByteArray internalBuffer;
    clsHttpHelper internalBuffer;
//    QByteArray externalBuffer;
    clsHttpHelper externalBuffer;
public slots:
    void dataFromInternal();
    void dataFromExternal();

    void internalDiscounnected();
    void externalDiscounnected();
    void slotErrorHandler(QString message);
//    void slotErrorHttpHandler(QString message);
signals:
    void someError(QString message);
};

#endif // SINGLEHANDLER_H
