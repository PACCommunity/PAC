#ifndef WEBSOCKETCLIENTWRAPPER_H
#define WEBSOCKETCLIENTWRAPPER_H

#include "websockettransport.h"

#include <QObject>
#include <QtWebSockets/QWebSocket>

QT_BEGIN_NAMESPACE

class WebSocketTransport;

class WebSocketClientWrapper : public QObject
{
    Q_OBJECT

public:
    WebSocketClientWrapper(const QUrl &url, QObject *parent = 0);

Q_SIGNALS:
    void clientConnected(WebSocketTransport* client);
    void transmit_to_gui(QString message);

private Q_SLOTS:
    void handleNewConnection();
    /** Receive the news from the web socket */
    void receive_from_transport(QString data);

private:
    QUrl m_url;
    QWebSocket m_webSocket;
    WebSocketTransport *m_websockettransport;
};

QT_END_NAMESPACE

#endif // WEBSOCKETCLIENTWRAPPER_H
