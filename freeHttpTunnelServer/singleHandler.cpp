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
    this->connect(&this->internalBuffer,SIGNAL(sigError(QString)),this,SLOT(slotHandleHttpError(QString)));
}

void singlehandler::dataFromExternal()
{
    //    qDebug()<<"dataFromInternal"<<"this->thread()"<<this->thread();
    //    qDebug()<<"dataFromInternal"<<"this->parent()"<<this->parent();
    //    qDebug()<<"dataFromInternal"<<"QThread::currentThread ()"<<QThread::currentThread ();

    this->externalBuffer.append(this->externalTcpSocket->readAll());
    this->logOutput("Data From External");
    //do some proccess on data

    //if needed
    //scenario changed, just append the data, whenever user request i will send him a response!
    //this->externalTcpSocket->write(this->internalBuffer.getByResponseHeader());
    //scenario chaned again, i wil send him if he is realy waiting for me :-x

    if(this->isclientwaiting || 1)
    {

        QByteArray temp = this->externalBuffer.getByResponseHeader();

        this->internalTcpSocket->write(temp);
        this->internalTcpSocket->waitForBytesWritten();
        this->logOutput(QString("in external sent %1").arg(temp.size()));
        this->isclientwaiting = 0;
    }
}

void singlehandler::dataFromInternal()
{
    //    qDebug()<<"dataFromExternal"<<"this->thread()"<<this->thread();
    //    qDebug()<<"dataFromExternal"<<"this->parent()"<<this->parent();
    //    qDebug()<<"dataFromExternal"<<"QThread::currentThread()"<<QThread::currentThread();
    this->internalBuffer.append(this->internalTcpSocket->readAll());
    this->logOutput("Data From Internal");
    //do some proccess on data
    //if needed
    //deque som data from buffer and que tosend buffer

    QByteArray temp = this->internalBuffer.getAfterRemoveHeader();
    this->logOutput(QString("net income : %1").arg(temp.size()));
    if(temp.size() > 0)
    {
        this->isclientwaiting = 1;
    }
    this->externalTcpSocket->write(temp);
    this->externalTcpSocket->waitForBytesWritten();
    this->logOutput(QString("in internal  sent %1").arg(temp.size()));
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
/*    if(this->internalTcpSocket->state() == QTcpSocket::ConnectedState)
    {
        this->internalTcpSocket->disconnectFromHost();
    }
    if(this->internalTcpSocket->state() != QTcpSocket::UnconnectedState)
        this->internalTcpSocket->waitForDisconnected();

    if(this->externalTcpSocket->state() == QTcpSocket::ConnectedState)
    {
        this->externalTcpSocket->disconnectFromHost();
    }

    if(this->externalTcpSocket->state() != QTcpSocket::UnconnectedState)
        this->externalTcpSocket->waitForDisconnected();
//    this->connect(this->internalTcpSocket,SIGNAL(readyRead()),this,SLOT(dataFromInternal()));
//    this->connect(this->externalTcpSocket,SIGNAL(readyRead()),this,SLOT(dataFromExternal()));
    this->logOutput("GoodBye");
//    this->thread()->quit();
    */
}


void singlehandler::slotHandleHttpError(QString msg)
{
    this->logOutput(QString("HttpError: ").append(msg));
}
