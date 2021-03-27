#include "mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QTranslator>
#include <QDateTime>

#include "core.h"

static QScopedPointer<QFile> huntLogFile;
static qint64 huntMaxLogFileSize = 8 * 1024 * 1024;

void huntQtMessageHandle(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    QString dt = QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm:ss");
    const char *loglevel;
    switch (type) {
    case QtDebugMsg:
        loglevel = "DEBUG";
        break;
    case QtInfoMsg:
        loglevel = "INFO ";
    case QtWarningMsg:
        loglevel = "WARN ";
        break;
    case QtCriticalMsg:
        loglevel = "ERROR";
        break;
    case QtFatalMsg:
        loglevel = "FATAL";
        break;
    default:
        loglevel = "WHAT ";
    }
    QString txt = QString("[%1 %2 %3\n").arg(dt, loglevel, msg);
    QMutexLocker locker(&mutex);
    if (huntLogFile->size() > huntMaxLogFileSize) {
        huntLogFile->resize(0);
    }
    huntLogFile->write(txt.toUtf8());
}

int main(int argc, char *argv[])
{
//    QApplication::setStyle("Fusion");
    QApplication app(argc, argv);
    QDir appdir(QApplication::applicationDirPath());

    // write qt message to file hunt.log
    QDir logfile(appdir.filePath("hunt.log"));
    huntLogFile.reset(new QFile(appdir.filePath("hunt.log")));
    huntLogFile.data()->open(QFile::Append | QFile::Text);
    qInstallMessageHandler(huntQtMessageHandle);

    QString locale = QLocale::system().name();
    auto localepath = appdir.filePath(QString("hunt_%1.qm").arg(locale));
    QScopedPointer<QTranslator> translator(new QTranslator);
    if (translator->load(localepath)) {
        HUNT_LOG_DEBUG << QString("find locale %1").arg(localepath);
    } else {
        HUNT_LOG_DEBUG << QString("can't find locale %1").arg(localepath);
    }
    app.installTranslator(translator.data());

    MainWindow w;
    w.show();
    return app.exec();
}
