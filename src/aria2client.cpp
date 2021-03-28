#include "aria2client.h"

#include <QUuid>

#include "scopeguard.h"

namespace hunt {

Aria2Client::Aria2Client(QObject *parent)
    : QObject(parent)
    , m_webSocket(new QWebSocket)
    , m_port(6800)
    , m_callbacks()
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

QString Aria2Client::getJsonID(const QJsonObject &document)
{
    auto it = document.find("id");
    if (it == document.end()) {
        return "";
    }
    return it->toString();
}
QString Aria2Client::getJsonError(const QJsonObject &document)
{
    auto it = document.find("error");
    if (it == document.end()) {
        return "";
    }
    return QJsonDocument(it.value().toObject()).toJson(QJsonDocument::Compact);
}

void Aria2Client::onTextMessageReceived(const QString &message)
{
    QJsonParseError err{};
    auto document = QJsonDocument::fromJson(message.toUtf8(), &err);
    if (err.error || !document.isObject()) {
        HUNT_LOG_WARN << "got invalid aria2c response " << message;
        return;
    }
    auto obj = document.object();
    auto id = getJsonID(obj);
    HUNT_ON_SCOPE_EXIT { m_callbacks.remove(id); };

    auto error = getJsonError(obj);
    if (!error.isEmpty()) {
        HUNT_LOG_WARN << "aria2c returns error" << message;
        return;
    }
    auto it = obj.find("result");
    if (it == obj.end()) {
        return;
    }
    auto callback = m_callbacks.find(id);
    if (callback == m_callbacks.end()) {
        return;
    }
    callback.value()(it.value());
}

QString Aria2Client::aria2getGlobalStat(Aria2Callback callback)
{
    QJsonObject obj;
    auto id = QUuid::createUuid().toString();
    obj.insert("id", id);
    obj.insert("method", "aria2.getGlobalStat");
    auto msg = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    auto send = m_webSocket->sendBinaryMessage(msg);
    if (send != msg.size()) {
        return "";
    }
    return id;
}

} // namespace hunt