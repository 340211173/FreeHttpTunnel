#include <QtCore/QCoreApplication>
#include "stuConnectionConfig.h"
#include "dispatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int port = 8811;
    stucConneectionConfig connectionconfig;
    connectionconfig.address = "127.0.0.1";
    connectionconfig.port=8888;

    dispatcher *dis =  new dispatcher(connectionconfig);
    int reslisten = dis->listen(QHostAddress::Any,port);

    if(!reslisten)
    {
        qDebug()<<"server failed to listen";
    }

    return a.exec();
}
