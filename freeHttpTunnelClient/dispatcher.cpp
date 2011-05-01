#include "dispatcher.h"
#include "singleManager.h"

dispatcher::dispatcher(stucConneectionConfig connectionconfig,QObject *parent) :
        QTcpServer(parent)
{
    this->threadnumber=0;
    this->connectionconfig = connectionconfig;
//    qDebug()<<"dispatcher:"<<"this->thread()"<<this->thread();
}


void dispatcher::incomingConnection(int socketDescriptor)
{
    singleManager *thread = new singleManager(socketDescriptor,threadnumber,connectionconfig, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), this, SLOT(eybaba()));
    thread->start();
    qDebug()<<"Thread number "<<this->threadnumber++<<" started.";
}

void dispatcher::eybaba()
{
    qDebug()<<"eybaba, some Thread died.";
}
