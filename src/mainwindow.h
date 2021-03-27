#ifndef HUNT_MAINWINDOW_H
#define HUNT_MAINWINDOW_H

#include <QMainWindow>

#include "centralwidget.h"
#include "menubar.h"
#include "statusbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() noexcept override;

private:
    StatusBar *m_statusbar;
    MenuBar *m_menubar;
    CentralWidget *m_centralWidget;
};
#endif // HUNT_MAINWINDOW_H
