#ifndef WEBSOCKETTRANSPORT_H
#define WEBSOCKETTRANSPORT_H

//#include "bitcoingui.h"

#include <QtWebChannel/QWebChannelAbstractTransport>
#include <QtWebSockets/QWebSocket>

QT_BEGIN_NAMESPACE

class WebSocketTransport : public QWebChannelAbstractTransport
{
    Q_OBJECT
public:
    explicit WebSocketTransport(QWebSocket *socket);
    virtual ~WebSocketTransport();

    void sendMessage(const QJsonObject &message) Q_DECL_OVERRIDE;

//Q_SIGNALS:
//	void transmit_to_gui(QString message);

private Q_SLOTS:
    void textMessageReceived(const QString &message);

private:
    QWebSocket *m_socket;
};

#endif // WEBSOCKETTRANSPORT_H