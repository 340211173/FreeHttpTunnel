#include "clsClientHandler.h"
#include <QtCore>

clsClientHandler::clsClientHandler(int _socketdiscriptor,QHostAddress _forwardHost,int _forwardPort,int _id,QObject *_parent) :
        QObject(_parent)
{
    this->forwardHost =_forwardHost;
    this->forwardPort = _forwardPort;
    this->id = _id;

    this->isPreRequestFinished = true;//coz there is no pre request
    this->internalTcpSocket = new QTcpSocket();

    this->externalTcpSocket= new QTcpSocket();


    if (!this->internalTcpSocket->setSocketDescriptor(_socketdiscriptor)) {
        //emit error(tcpSocket.error());
        this->logOutput(this->internalTcpSocket->errorString());
        return;
    }

    this->externalTcpSocket->connectToHost(this->forwardHost,this->forwardPort);
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


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotGetRestOfIceCream()));
    timer->start(1000);

}
void clsClientHandler::slotGetRestOfIceCream()
{

    //if the privous request finished
    if(this->isPreRequestFinished)
    {
        this->logOutput("Chocolote Ice Cream");
        QByteArray temp = this->internalBuffer.getByRequestGetHeader(this->forwardHost.toString());
        this->externalTcpSocket->write(temp);
        this->externalTcpSocket->waitForBytesWritten();
        this->isPreRequestFinished=false;
        this->logOutput(QString("written in IceCream to external %1").arg(temp.size()));
    }
}

void clsClientHandler::dataFromInternal()
{
    //    qDebug()<<"dataFromInternal"<<"this->thread()"<<this->thread();
    //    qDebug()<<"dataFromInternal"<<"this->parent()"<<this->parent();
    //    qDebug()<<"dataFromInternal"<<"QThread::currentThread ()"<<QThread::currentThread ();
    this->internalBuffer.append(this->internalTcpSocket->readAll());
    this->logOutput("Data From Internal");
    //do som e proccess on data
    //if needed
    //deque som data from buffer and que to send buffer

    QByteArray temp = this->internalBuffer.getByRequestPostHeader(this->forwardHost.toString());
    this->externalTcpSocket->write(temp);
    this->externalTcpSocket->waitForBytesWritten();
    this->logOutput(QString("written in Internal %1").arg(temp.size()));
}

void clsClientHandler::dataFromExternal()
{
    //    qDebug()<<"dataFromExternal"<<"this->thread()"<<this->thread();
    //    qDebug()<<"dataFromExternal"<<"this->parent()"<<this->parent();
    //    qDebug()<<"dataFromExternal"<<"QThread::currentThread()"<<QThread::currentThread();
    this->externalBuffer.append(this->externalTcpSocket->readAll());
    this->logOutput("Data From Extrnal");
    //do some proccess on data
    //if needed
    //deque som data from buffer and que tosend buffer
    bool isCompleted=false;
    QByteArray temp = this->externalBuffer.getAfterRemoveResponseHeader(isCompleted);
    this->isPreRequestFinished =isCompleted;
    this->internalTcpSocket->write(temp);
    this->internalTcpSocket->waitForBytesWritten();
    this->logOutput(QString("written in External %1").arg(temp.size()));
}

void clsClientHandler::externalDiscounnected()
{
    this->logOutput("External Disscountected.");
    this->sayGoodBye();
}

void clsClientHandler::internalDiscounnected()
{
    this->logOutput("Internal Disscountected.");
    this->sayGoodBye();
}

void clsClientHandler::slotErrorHandler(QString msg)
{
    this->logOutput(QString("Error Occured:").append(msg));
    this->sayGoodBye();
}

void clsClientHandler::logOutput(QString msg)
{
    qDebug()<<"single Handler"<<this->id<<" : "<<msg;
}

void clsClientHandler::sayGoodBye()
{
    this->logOutput("Say Good Bye.");
    /*
    if(this->internalTcpSocket->state() == QTcpSocket::ConnectedState)
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
    this->thread()->quit();
    */
}
