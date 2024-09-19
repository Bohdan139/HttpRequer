#include "networkconnector.h"

NetworkConnector::NetworkConnector(QObject *parent)
    : QObject{parent}
{
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply)
    {
       if (reply->error())
       {
           qDebug() << reply->errorString();
       }
       this->result.first = reply->header(QNetworkRequest::ContentTypeHeader);
       this->result.second = reply->readAll();
       emit dataCome();
    });

}

void NetworkConnector::connectToServer(int method,const QUrl &Url, const QString &header, const QByteArray *data)
{
    request.setUrl(Url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(header));

    switch (method) {
    case 0:
        manager->get(request);
        break;
    case 1:
        if(data == nullptr)
        {
            manager->post(request, QByteArray(0));
        }
        else
        {
            manager->post(request, *data);
        }
        break;
    case 2:
        manager->head(request);
        break;
    case 3:
        if(data == nullptr)
        {
            manager->put(request, QByteArray(0));
        }
        else
        {
            manager->put(request, *data);
        }
    case 4:
        manager->deleteResource(request);
        break;
    default:
        break;
    }


}

QPair<QVariant, QByteArray> NetworkConnector::getResult() const
{
    return result;
}
