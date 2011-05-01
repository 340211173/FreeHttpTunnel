#include <QtCore>
#include "clsHttpHelper.h"

clsHttpHelper::clsHttpHelper(QObject *parent) :
        QObject(parent){
    this->state = 0;
    this->remainingcontenttosend = 0;

}

QByteArray clsHttpHelper::getByRequestHeader(QString domain){

    //add HTTP Header
    QByteArray endline;
    endline.append(13);
    endline.append(10);
    QByteArray header;

    header.append("POST ");
    header.append(this->generateUrl());
    header.append(" HTTP/1.1");
    header.append(endline);

    header.append("Host: ");
    header.append(domain);
    header.append(endline);

    header.append("Keep-Alive: 115");
    header.append(endline);

    header.append("Proxy-Connection: keep-alive");
    header.append(endline);

    header.append("Pragma: no-cache");
    header.append(endline);

    header.append("Cache-Control: no-cache");
    header.append(endline);

    header.append("Content-Type: application/octet-stream");
    header.append(endline);
    header.append("Content-Length: ");
    header.append(QString().number(this->buffer.size(),10));
    header.append(endline);

    header.append(endline);

    QByteArray result;
    result.append(header);
    result.append(this->buffer);
    this->buffer.clear();
    return result;
}

QByteArray clsHttpHelper::getByResponseHeader(){
    //add HTTP Header
    QByteArray endline;
    endline.append(13);
    endline.append(10);
    QByteArray header;

    header.append("HTTP/1.1 200 OK");
    header.append(endline);

    header.append("Accept-Ranges: bytes");
    header.append(endline);

    header.append("Connection: keep-alive");
    header.append(endline);

    header.append("Proxy-Connection: keep-alive");
    header.append(endline);

    header.append("Content-Type: application/octet-stream");
    header.append(endline);

    header.append("Content-Length: ");
    header.append(QString().number(this->buffer.size(),10));
    header.append(endline);

    header.append(endline);

    QByteArray result;
    result.append(header);
    result.append(this->buffer);
    this->buffer.clear();
    return result;
}

QBool clsHttpHelper::hasAny(){
    return QBool(false);
}

QByteArray clsHttpHelper::getAfterRemoveHeader(){
    this->logOutput("start afterremove");
    QByteArray result;
    QByteArray endline;
    endline.append(13);
    endline.append(10);
    QByteArray endlineendline;
    endlineendline.append(endline);
    endlineendline.append(endline);

    if(this->state == 0)
    {
        this->logOutput("afterremove: state is 0");
        //if header is complete
        int taheheader = this->buffer.indexOf(endlineendline);
        this->logOutput(QString().number(this->buffer.size()));
        if(taheheader>0)
        {
            this->logOutput("afterremove: taheheader>0");
            //header completed,
            //how much data should i recieve

            //find the content-length
            QByteArray alt =this->buffer.mid(0,taheheader).toUpper();
            QByteArray findstring;
            findstring.append(endline);
            findstring.append("CONTENT-LENGTH");
            int startlength = alt.indexOf(findstring);
            if(startlength < 0)//this is error header completed but there is no content-length!
            {
                emit this->sigError("No Content-Length");
            }else
            {
                this->logOutput("afterremove: content-length finded");
                int startnumber = alt.indexOf(":",startlength) +1;
                int endnumber =this->buffer.indexOf(endline,startnumber);//from buffer not from alt
                if(startnumber<0 || endnumber<0)//this is error header completed but there is no content-length!
                {
                    emit this->sigError("Content-Length without value!");
                }else
                {
                    this->logOutput("afterremove: length finded");
                    //convert to string
                    bool ok;
                    QString num =alt.mid(startnumber,endnumber);
                    int length = num.trimmed().toInt(&ok);
                    this->logOutput(QString("Length is %1, original is %2, start is %3, end is %4").arg(length).arg(num).arg(startnumber).arg(endnumber));
                    if(ok)
                    {
                        this->state = 1;
                        //remove the header
                        this->buffer.remove(0,taheheader+4);

                        this->remainingcontenttosend = length;
                    }else//error
                    {
                        emit this->sigError(QString("bad value in Content-Length ").append(alt.mid(startnumber,endnumber)));
                    }
                }
            }
        }else
        {
            this->logOutput("afterremove: header not finded.");
        }
    }

    if(this->state==1)
    {
        result =this->buffer.mid(0,this->remainingcontenttosend);
        this->remainingcontenttosend-=result.size();
        if(this->remainingcontenttosend <=0)
        {
            this->state=0;
        }
    }

    return result;
}

int clsHttpHelper::append(QByteArray data){
    this->buffer.append(data);
    return data.size();
}

void clsHttpHelper::clear()
{
    this->buffer.clear();
}

QString clsHttpHelper::generateUrl()
{
    return QString("/").append("pic1.jpg");
}

void  clsHttpHelper::logOutput(QString msg)
{
    qDebug()<<"clsHttpHelper"<<msg;
}
