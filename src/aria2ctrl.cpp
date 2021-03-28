#include "aria2ctrl.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>

#include "core.h"

namespace hunt {

QString Aria2Ctrl::findAria2c()
{
#if defined(HUNT_WIN)
    static const char *aria2c_exec = "aria2c.exe";
#else
    static const char *aria2c_exec = "aria2c";
#endif
    QDir path(QApplication::applicationDirPath());
    auto exec = path.filePath(aria2c_exec);
    if (QFileInfo::exists(exec)) {
        return exec;
    }
    return QString(aria2c_exec);
}

Aria2Ctrl::Aria2Ctrl(QObject *parent)
    : QObject{parent}
    , m_aria2c(new QProcess{this})
{
    QDir path(QApplication::applicationDirPath());
    m_aria2c->setStandardOutputFile(path.filePath("aria2c.console.log"));
    m_aria2c->setStandardErrorFile(path.filePath("aria2c.error.console.log"));
}

Aria2Ctrl::~Aria2Ctrl()
{
    terminate(true);
    delete m_aria2c;
}

qint32 Aria2Ctrl::findPort()
{
    static qint32 port = 56799;
    return ++port;
}

void Aria2Ctrl::start(bool wait)
{
    m_port = findPort();
    QStringList args;
    args << "--enable-rpc";
    args << QString("--rpc-listen-port=%1").arg(m_port);
    args << "--enable-color=false";
    args << "--rlimit-nofile=65535";
    QDir path(QApplication::applicationDirPath());
    args << "-l" << path.filePath("aria2c.log");
    m_aria2c->start(findAria2c(), args, QProcess::ReadOnly);
    HUNT_LOG_DEBUG << "aria2c start and listen on " << m_port;
    if (wait) {
        m_aria2c->waitForStarted();
    }
}

qint64 Aria2Ctrl::pid() const
{
    return m_aria2c->processId();
}

bool Aria2Ctrl::running() const
{
    return m_aria2c->state() == QProcess::Running;
}

void Aria2Ctrl::terminate(bool wait)
{
    if (!running()) {
        return;
    }
    m_aria2c->terminate();
    if (running()) {
        m_aria2c->kill();
    }
    if (wait) {
        m_aria2c->waitForFinished();
    }
}

} // namespace hunt
