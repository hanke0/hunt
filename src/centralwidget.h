#ifndef HUNT_CENTRAL_WIDGET_H
#define HUNT_CENTRAL_WIDGET_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QWidget>

#include "sidebar.h"

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget() noexcept override = default;

    void setUp(QMainWindow *mainWindow);

private:
    SideBar *sidebar;
    QStackedWidget *stackedWidget;
};

#endif //HUNT_CENTRAL_WIDGET_H
