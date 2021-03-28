#ifndef HUNT_STATUSBAR_H
#define HUNT_STATUSBAR_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStatusBar>

#include "aria2client.h"
#include "aria2ctrl.h"
#include "eventlogwidget.h"

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar() override;

    void setUp(QMainWindow *mainWindow);

private:
    void setupAria();
    void setupStatusBarEventLog(QMainWindow *mainWindow);

private slots:
    void on_ariaConnectionStateChange(QAbstractSocket::SocketState state);

private:
    hunt::Aria2Ctrl *m_ariaProcess;
    QLabel *m_ariaLabel;
    hunt::Aria2Client *m_ariaClient;
    EventLogWidget *m_eventLogWidget;
    QPushButton *m_eventLogButton;
};

#endif //HUNT_STATUSBAR_H
