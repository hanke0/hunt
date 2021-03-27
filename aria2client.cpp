#include "aria2client.h"

namespace hunt {

Aria2Client::Aria2Client(QObject *parent)
    : QObject(parent)
    , m_webSocket(new QWebSocket)
    , m_port(6800)
    , m_debug(false)
{
    m_webSocket->setParent(this);

    connect(m_webSocket, &QWebSocket::connected, this, &Aria2Client::onAriaConnected);
    connect(m_webSocket, &QWebSocket::stateChanged, this, &Aria2Client::ariaConnectionStateChange);
}

Aria2Client::~Aria2Client()
{
    delete m_webSocket;
}

void Aria2Client::setPort(qint32 port) noexcept
{
    m_port = port;
}

void Aria2Client::openConnect()
{
    if (m_webSocket->isValid()) {
        return;
    }
    QUrl url(QString("ws://localhost:%1/jsonrpc").arg(m_port));
    m_webSocket->open(url);
}

bool Aria2Client::isValid() const
{
    return m_webSocket->isValid();
}

void Aria2Client::onAriaConnected()
{
    connect(m_webSocket,
            &QWebSocket::textMessageReceived,
            this,
            &Aria2Client::onTextMessageReceived);
}

void Aria2Client::onTextMessageReceived(QString message) {}

} // namespace hunt