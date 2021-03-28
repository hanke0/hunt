#ifndef HUNT_CORE_H
#define HUNT_CORE_H

#include <QMetaEnum>
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>

#if (defined(_WIN32) || defined(_WIN64))
#define HUNT_WIN
#define HUNT_PLATFORM "win32"
#else
#define HUNT_POSIX
#define HUNT_PLATFORM "posix"
#endif

#ifndef __HUNT_FILE__
#define __HUNT_FILE__ ""
#endif

#define HUNT_LOG_LEVEL(lvl) lvl().nospace() << __HUNT_FILE__ << ":" << __LINE__ << "] - "
#define HUNT_LOG_DEBUG HUNT_LOG_LEVEL(qDebug)
#define HUNT_LOG_INFO HUNT_LOG_LEVEL(qInfo)
#define HUNT_LOG_WARN HUNT_LOG_LEVEL(qWarning)
#define HUNT_LOG_CRITICAL HUNT_LOG_LEVEL(qCritical)
#define HUNT_LOG_FATAL HUNT_LOG_LEVEL(qFatal)

template<typename QEnum>
QString QtEnumToQString(const QEnum value)
{
    return QMetaEnum::fromType<QEnum>().valueToKey(value);
}

#define HUNT_TR(key, ...) ::QCoreApplication::translate("hunt", key, ##__VA_ARGS__)

#endif // HUNT_CORE_H
