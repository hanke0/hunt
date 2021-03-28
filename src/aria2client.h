#ifndef HUNT_ARIA2CLIENT_H
#define HUNT_ARIA2CLIENT_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

#include "core.h"

namespace hunt {
class Aria2Client : public QObject
{
    Q_OBJECT
public:
    typedef void (*Aria2Callback)(const QJsonValue &data);

    explicit Aria2Client(QObject *parent = nullptr);
    ~Aria2Client() override;

public:
    void setPort(qint32 port) noexcept;
    void openConnect();
    bool isValid() const;
    QString aria2getGlobalStat(Aria2Callback callback);

private:
    QString getJsonID(const QJsonObject &document);
    QString getJsonError(const QJsonObject &document);

Q_SIGNALS:
    void ariaConnectionStateChange(QAbstractSocket::SocketState);

private Q_SLOTS:
    void onAriaConnected();
    void onTextMessageReceived(const QString &message);

private:
    QWebSocket *m_webSocket;
    qint32 m_port;
    QMap<QString, Aria2Callback> m_callbacks;
};

} // namespace hunt

#endif //HUNT_ARIA2CLIENT_H
