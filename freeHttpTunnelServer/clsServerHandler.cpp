#include <QtCore>
#include "clsServerHandler.h"

clsServerHandler::clsServerHandler(int _socketdiscriptor,QHostAddress _forwardHost,int _forwardPort, int _id,QObject *_parent):
        QObject(_parent)
{

    this->id = _id;

    this->forwardHost  = _forwardHost;
    this->forwardPort = _forwardPort;

    this->internalTcpSocket = new QTcpSocket();

    this->externalTcpSocket= new QTcpSocket();

    if (!this->internalTcpSocket->setSocketDescriptor(_socketdiscriptor)) {
        //emit error(tcpSocket.error());
        this->logOutput(this->internalTcpSocket->errorString());
        //        return;
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
    this->connect(&this->internalBuffer,SIGNAL(sigError(QString)),this,SLOT(slotHandleHttpError(QString)));
}

void clsServerHandler::dataFromExternal()
{
    this->externalBuffer.append(this->externalTcpSocket->readAll());
//    this->logOutput(QString("Data From External %1").arg(this->externalBuffer.size()));
    //do some proccess on data

    //if needed
    //scenario changed, just append the data, whenever user request i will send him a response!
    //this->externalTcpSocket->write(this->internalBuffer.getByResponseHeader());
    //scenario chaned again, i wil send him if he is realy waiting for me :-x
    //scenario chaned again, whay not cobine both of them

    if(this->isclientwaiting)
    {
        this->logOutput("Client is wainting");
        QByteArray temp = this->externalBuffer.getByResponseHeader();

        this->internalTcpSocket->write(temp);
        this->internalTcpSocket->waitForBytesWritten();
        this->logOutput(QString("in external sent to internal %1").arg(temp.size()));
        this->isclientwaiting = 0;
    }else
    {
        this->logOutput("Client is NOT  wainting");
    }
}

void clsServerHandler::dataFromInternal()
{
    this->internalBuffer.append(this->internalTcpSocket->readAll());
    this->logOutput("Data From Internal");
    //do some proccess on data
    //if needed
    //deque som data from buffer and que tosend buffer


    if( 0 == this->isclientwaiting )
    {
        if(this->internalBuffer.getAfterRemoveGetHeader())
        {
            this->logOutput(QString("GET REQUEST, data in external buffer: %1").arg(this->externalBuffer.size()));
            this->isclientwaiting = 1;
        }else
        {
            this->logOutput(QString("POST REQUEST, data in external buffer: %1").arg(this->externalBuffer.size()));
            QByteArray temp = this->internalBuffer.getAfterRemoveHeader();
            this->logOutput(QString("net income : %1").arg(temp.size()));
            if(temp.size() > 0)
            {
                this->logOutput("Post Request Completed");
                this->isclientwaiting = 1;
            }
            this->externalTcpSocket->write(temp);
            this->externalTcpSocket->waitForBytesWritten();
            this->logOutput(QString("in internal  sent to external %1").arg(temp.size()));
        }


    }

    if( 1 == this->isclientwaiting )
    {

        this->logOutput("seems client is wainting now");
        QByteArray temp = this->externalBuffer.getByResponseHeader();

        this->internalTcpSocket->write(temp);
        this->internalTcpSocket->waitForBytesWritten();
        this->logOutput(QString("in internal sent to internal %1").arg(temp.size()));
        this->isclientwaiting = 0;
    }
}

void clsServerHandler::externalDiscounnected()
{
    this->logOutput("External Disscountected.");
    this->sayGoodBye();
}

void clsServerHandler::internalDiscounnected()
{
    this->logOutput("Internal Disscountected.");
    this->sayGoodBye();
}

void clsServerHandler::logOutput(QString msg)
{
    qDebug()<<"server Handler"<<this->id<<" : "<<msg;
}


void clsServerHandler::sayGoodBye()
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


void clsServerHandler::slotHandleHttpError(QString msg)
{
    this->logOutput(QString("HttpError: ").append(msg));
}
