#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QTcpServer>
#include "stuConnectionConfig.h"

class dispatcher : public QTcpServer
{
    Q_OBJECT
public:
    explicit dispatcher(stucConneectionConfig connectionconfig,QObject *parent = 0);

protected:
    void incomingConnection(int socketDescriptor);
private:
    int threadnumber;
    stucConneectionConfig connectionconfig;
private slots:
    void eybaba();
};

#endif // DISPATCHER_H
