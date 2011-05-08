#include "clsServerDistpacher.h"
#include "clsServerHandler.h"

clsServerDistpacher::clsServerDistpacher(QHostAddress _forwardHost,int _forwardPort, QObject *_parent) :
        QTcpServer(_parent)
{
    this->threadnumber=0;
    this->forwardHost = _forwardHost;
    this->forwardPort = _forwardPort;
    //    qDebug()<<"dispatcher:"<<"this->thread()"<<this->thread();
}


void clsServerDistpacher::incomingConnection(int socketDescriptor)
{
    qDebug()<<"handler number "<<this->threadnumber++<<" started.";
    clsServerHandler* sh = new clsServerHandler(socketDescriptor,this->forwardHost,this->forwardPort,this->threadnumber++);
}

void clsServerDistpacher::eybaba()
{
    qDebug()<<"eybaba, some Thread died.";
}
