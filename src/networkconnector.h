#ifndef NETWORKCONNECTOR_H
#define NETWORKCONNECTOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>

class NetworkConnector : public QObject
{
    Q_OBJECT
public:
    explicit NetworkConnector(QObject *parent = nullptr);

    void connectToServer(int method,const QUrl& Url, const QString& header, const QByteArray* data = nullptr);

    QPair<QVariant, QByteArray> getResult() const;

signals:
    void dataCome();

private:

    QNetworkAccessManager* manager;
    QNetworkRequest request;
    QPair<QVariant, QByteArray> result;

};

#endif // NETWORKCONNECTOR_H
