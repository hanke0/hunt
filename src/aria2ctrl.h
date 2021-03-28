#ifndef HUNT_ARIA2CTRL_H
#define HUNT_ARIA2CTRL_H

#include <memory>
#include <string>
#include <vector>

#include <QProcess>
#include <QString>

namespace hunt {
class Aria2Ctrl : public QObject
{
    Q_OBJECT
public:
    explicit Aria2Ctrl(QObject *parent = nullptr);
    ~Aria2Ctrl() override;
    void start(bool wait = false);

public:
    bool running() const;
    void terminate(bool wait = false);
    qint64 pid() const;

private:
    static QString findAria2c();
    static qint32 findPort();

public:
    QProcess *m_aria2c;
    qint32 m_port = 0;
};

} // namespace hunt

#endif // HUNT_ARIA2CTRL_H
