#include "websocketclientwrapper.h"
#include <QtWebSockets/QWebSocketServer>
#include "websockettransport.h"

QT_BEGIN_NAMESPACE

WebSocketClientWrapper::WebSocketClientWrapper(const QUrl &url, QObject *parent)
    : QObject(parent)
    , m_url(url)
{
    qWarning() << "Open WebSocket connection: " << m_url;
    connect(&m_webSocket, &QWebSocket::connected,
            this, &WebSocketClientWrapper::handleNewConnection);
    qDebug() << "connecting...";
    m_webSocket.open(url);
}

void WebSocketClientWrapper::handleNewConnection()
{
    qWarning() << "WebSocket connected: " << m_url;
    Q_EMIT clientConnected(new WebSocketTransport(&m_webSocket));
}
