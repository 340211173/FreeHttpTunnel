#include "clsHttpHelper.h"

clsHttpHelper::clsHttpHelper(QObject *parent) :
        QObject(parent)
{
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

    //        header.append("Content-Type: application/x-www-form-urlencoded");
    //        header.append(endline);
    header.append("Content-Length: ");
    header.append(this->buffer.size());
    header.append(endline);

    QByteArray result;
    result.append(header);
    result.append(this->buffer);
    return result;
}

QByteArray clsHttpHelper::getByResponseHeader(){
    return QByteArray();
}

QBool clsHttpHelper::hasAny(){
    return QBool(false);
}

QByteArray clsHttpHelper::getAfterRemoveHeader(){

    QByteArray endline;
    endline.append(13);
    endline.append(10);
    QByteArray endlineendline;
    endlineendline.append(endline);
    endlineendline.append(endline);

    //if header is complete
    int taheheader = this->buffer.indexOf(endlineendline);
    if(taheheader>0)
    {
        //header completed,
        //how much data should i recieve
        // start counting
        QByteArray alt =this->buffer.toUpper();
        QByteArray findstring;
        findstring.append(endline);
        findstring.append("CONTENT-LENGTH");
        int startlength = alt.indexOf(findstring);
        if(startlength < 0)//this is error header completed but there is no content-length!
        {

        }else
        {
            int startnumber = alt.indexOf(":",startlength);
            int endnumber =alt.indexOf(endline);
            if(startnumber<0 || endnumber<0)//this is error header completed but there is no content-length!
            {
                //convert to string
            }
        }

        //find the content-length
    }

    return QByteArray();
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
