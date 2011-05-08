#include <QtCore/QCoreApplication>
#include "stuConnectionConfig.h"
#include "clsServerDistpacher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int listenPort = 8888;
    QHostAddress forwardHost = QHostAddress("127.0.0.1");
    int forwardPort=3128;

    QCoreApplication::setOrganizationName("Lotus");
    QCoreApplication::setOrganizationDomain("lotux.ir");
    QCoreApplication::setApplicationName("freeHttpTunnelServers");


    clsServerDistpacher *dis =  new clsServerDistpacher(forwardHost,forwardPort);
    int reslisten = dis->listen(QHostAddress::Any,listenPort);

    if(!reslisten)
    {
        qDebug()<<"server failed to listen";
    }else
    {
        return a.exec();
    }
}
