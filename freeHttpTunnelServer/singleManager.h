#ifndef SINGLEMANAGER_H
#define SINGLEMANAGER_H

#include <QThread>
#include <QTcpSocket>
#include "stuConnectionConfig.h"
#include "singleHandler.h"

class singleManager : public QThread
{
    Q_OBJECT
public:
    explicit singleManager(int socketdiscriptor,int id,stucConneectionConfig connectionconfig,QObject *parent = 0);
    void run();
public slots:
private:
    int id;
    int socketDescriptor;
    stucConneectionConfig connectionconfig;
//    singlehandler* sh;
};

#endif // SINGLEMANAGER_H
