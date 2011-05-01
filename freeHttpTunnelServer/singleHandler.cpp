#include "singleHandler.h"
#include <QtCore>

singlehandler::singlehandler(int socketdiscriptor,int id, stucConneectionConfig connectionconfig, QObject *parent) :
        QObject(parent)
{
    this->connectionconfig = connectionconfig;
    this->id = id;

    this->internalTcpSocket = new QTcpSocket(this);

    this->externalTcpSocket= new QTcpSocket(this);

    //    qDebug()<<"singlehandler:"<<"this->internalTcpSocket->thread()"<<this->internalTcpSocket->thread();
    //    qDebug()<<"singlehandler:"<<"this->externalTcpSocket->thread()"<<this->externalTcpSocket->thread();
    if (!this->internalTcpSocket->setSocketDescriptor(socketdiscriptor)) {
        //emit error(tcpSocket.error());
        this->logOutput(this->internalTcpSocket->errorString());
        return;
    }

    this->externalTcpSocket->connectToHost(this->connectionconfig.address,this->connectionconfig.port);
    if(this->externalTcpSocket->waitForConnected())
    {
        this->logOutput("external socket connected");
    }else
    {
        this->logOutput("external socket failed to connect");
    }
    //    this->logOutput("Sockets Connected.");
    this->connect(this->internalTcpSocket,SIGNAL(disconnected()),this,SLOT(internalDiscounnected()));
    this->connect(this->externalTcpSocket,SIGNAL(disconnected()),this,SLOT(externalDiscounnected()));
    //    this->logOutput("data signal/slot Connected.");
    this->connect(this->internalTcpSocket,SIGNAL(readyRead()),this,SLOT(dataFromInternal()));
    this->connect(this->externalTcpSocket,SIGNAL(readyRead()),this,SLOT(dataFromExternal()));
    //    this->logOutput("disccount signal/slot Connected.");
}

void singlehandler::dataFromInternal()
{
    //    qDebug()<<"dataFromInternal"<<"this->thread()"<<this->thread();
    //    qDebug()<<"dataFromInternal"<<"this->parent()"<<this->parent();
    //    qDebug()<<"dataFromInternal"<<"QThread::currentThread ()"<<QThread::currentThread ();
    QByteArray sendtoExternal;
    this->internalBuffer.append(this->internalTcpSocket->readAll());
    this->logOutput("Data From Internal");
    //do som e proccess on data
    //if needed
    if(true)
    {
        //deque som data from buffer and que tosend buffer
        sendtoExternal.append(this->internalBuffer);
        this->internalBuffer.clear();

        this->externalTcpSocket->write(sendtoExternal);
    }
}

void singlehandler::dataFromExternal()
{
    //    qDebug()<<"dataFromExternal"<<"this->thread()"<<this->thread();
    //    qDebug()<<"dataFromExternal"<<"this->parent()"<<this->parent();
    //    qDebug()<<"dataFromExternal"<<"QThread::currentThread()"<<QThread::currentThread();
    QByteArray sendtoInternal;
    this->externalBuffer.append(this->externalTcpSocket->readAll());
    this->logOutput("Data From Extrnal");
    //do some proccess on data
    //if needed
    if(true)
    {
        //deque som data from buffer and que tosend buffer
        sendtoInternal.append(this->externalBuffer);
        this->externalBuffer.clear();

        this->internalTcpSocket->write(sendtoInternal);
    }
}

void singlehandler::externalDiscounnected()
{
    this->logOutput("External Disscountected.");
    this->sayGoodBye();
}

void singlehandler::internalDiscounnected()
{
    this->logOutput("Internal Disscountected.");
    this->sayGoodBye();
}

void singlehandler::logOutput(QString msg)
{
    qDebug()<<"single Handler"<<this->id<<" : "<<msg;
}



void singlehandler::sayGoodBye()
{
    this->logOutput("Say Good Bye.");
    if(this->internalTcpSocket->state() == QTcpSocket::ConnectedState)
    {
        this->internalTcpSocket->disconnectFromHost();
        if(this->internalTcpSocket->state() == QTcpSocket::ConnectedState)
            this->internalTcpSocket->waitForDisconnected();
    }

    if(this->externalTcpSocket->state() == QTcpSocket::ConnectedState)
    {
        this->externalTcpSocket->disconnectFromHost();
        if(this->externalTcpSocket->state() == QTcpSocket::ConnectedState)
            this->externalTcpSocket->waitForDisconnected();
    }
    this->connect(this->internalTcpSocket,SIGNAL(readyRead()),this,SLOT(dataFromInternal()));
    this->connect(this->externalTcpSocket,SIGNAL(readyRead()),this,SLOT(dataFromExternal()));
    this->logOutput("GoodBye");
    this->thread()->quit();
}
