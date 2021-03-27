#ifndef HUNT_ARIA2CLIENT_H
#define HUNT_ARIA2CLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

#include "core.h"

namespace hunt {
class Aria2Client : public QObject
{
    Q_OBJECT
public:
    explicit Aria2Client(QObject *parent = nullptr);
    ~Aria2Client() override;

public:
    void setPort(qint32 port) noexcept;
    void openConnect();
    bool isValid() const;

Q_SIGNALS:
    void ariaConnectionStateChange(QAbstractSocket::SocketState);

private Q_SLOTS:
    void onAriaConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket *m_webSocket;
    qint32 m_port;
    bool m_debug;
};

} // namespace hunt

#endif //HUNT_ARIA2CLIENT_H
