#ifndef HUNT_MAINWINDOW_H
#define HUNT_MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

#include "aria2client.h"
#include "aria2ctrl.h"
#include "eventlogwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupAria();
    void setupStatusBarEventLog();

private slots:
    void on_ariaConnectionStateChange(QAbstractSocket::SocketState state);

private:
    Ui::MainWindow *ui;
    hunt::Aria2Ctrl *m_ariaProcess;
    QLabel *m_ariaLabel;
    hunt::Aria2Client *m_ariaClient;
    EventLogWidget *m_eventLogWidget;
    QPushButton *m_eventLogButton;
};
#endif // HUNT_MAINWINDOW_H
