#include "websockettransport.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include <QtWebSockets/QWebSocket>

#include <string>
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE

WebSocketTransport::WebSocketTransport(QWebSocket *socket)
: QWebChannelAbstractTransport(socket)
, m_socket(socket)
{
    connect(socket, &QWebSocket::textMessageReceived,
            this, &WebSocketTransport::textMessageReceived);
}

WebSocketTransport::~WebSocketTransport()
{

}

void WebSocketTransport::sendMessage(const QJsonObject &message)
{
    QJsonDocument doc(message);
    m_socket->sendTextMessage(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
}

void WebSocketTransport::textMessageReceived(const QString &messageData)
{
    cout << "Message in..." << endl;
    cout << messageData.toStdString() << endl;
    qDebug() << messageData;
    cout << "Message out..." << endl;
    //emit transmit_to_gui(messageData);
}
