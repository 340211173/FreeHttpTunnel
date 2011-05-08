#include "clsClientDispatcher.h"
#include "clsClientHandler.h"


clsClientDispatcher::clsClientDispatcher(QHostAddress _forwardHost, int _forwardport, QObject *_parent) :
        QTcpServer(_parent)
{
    this->handlerNumber=0;
    this->forwardHost = _forwardHost;
    this->forwardPort = _forwardport;

}


void clsClientDispatcher::incomingConnection(int _socketDescriptor)
{
    clsClientHandler *handler = new clsClientHandler(_socketDescriptor,this->forwardHost,this->forwardPort, this->handlerNumber, this);
//    connect(handler, SIGNAL(finished()), handler, SLOT(deleteLater()));
//    connect(handler, SIGNAL(finished()), this, SLOT(eybaba()));
//    thread->start();
    qDebug()<<"Handler number "<<this->handlerNumber++<<" started.";
}

void clsClientDispatcher::eybaba()
{
    qDebug()<<"eybaba, some Thread died.";
}
