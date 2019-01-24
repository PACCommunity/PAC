#include "websocketclientwrapper.h"
#include <QtWebSockets/QWebSocketServer>
#include "websockettransport.h"

#include <string>
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE

WebSocketClientWrapper::WebSocketClientWrapper(const QUrl &url, QObject *parent): QObject(parent), m_url(url)
{
    cout << "BeforeWrapper" << endl;
    QString str = m_url.toEncoded();
    cout << "Open WebSocket connection: " << str.toStdString() << endl;
    connect(&m_webSocket, &QWebSocket::connected,
            this, &WebSocketClientWrapper::handleNewConnection);
    cout << "connecting...";
    m_webSocket.open(url);
    cout << "AfterWrapper" << endl;
}

void WebSocketClientWrapper::handleNewConnection()
{
    cout << "BeforeConnecting" << endl;
    qWarning() << "WebSocket connected: " << m_url;
    Q_EMIT clientConnected(new WebSocketTransport(&m_webSocket));
    cout << "AfterConnecting" << endl;
}
