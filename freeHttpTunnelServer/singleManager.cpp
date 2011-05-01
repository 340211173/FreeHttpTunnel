#include <QTcpSocket>
#include "singleManager.h"

singleManager::singleManager(int socketdiscriptor,int id, stucConneectionConfig connectionconfig, QObject *parent) :
        QThread(parent)
{
    this->socketDescriptor = socketdiscriptor;
    this->connectionconfig = connectionconfig;
    this->id = id;
}

void singleManager::run()
{
//    qDebug()<<"run:"<<"QThread::currentThread()"<<QThread::currentThread();
//    qDebug()<<"run:"<<"this->thread()"<<this->thread();
//    qDebug()<<"run:"<<"this"<<this;
    singlehandler* sh = new singlehandler(this->socketDescriptor,this->id,this->connectionconfig);
    this->exec();
}
