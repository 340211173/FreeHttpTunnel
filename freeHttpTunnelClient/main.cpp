#include <QtCore/QCoreApplication>
#include "clsClientDispatcher.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int listenPort = 8811;


    QHostAddress forwardHost =QHostAddress ("127.0.0.1");
    int forwardPort = 8888;

    clsClientDispatcher  *dis =  new clsClientDispatcher(forwardHost ,forwardPort);
    int reslisten = dis->listen(QHostAddress::Any,listenPort );

    if(!reslisten)
    {
        qDebug()<<"server failed to listen";
    }

    return a.exec();
}
