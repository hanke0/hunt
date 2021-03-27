#ifndef HUNT_EVENTLOGWIDGET_H
#define HUNT_EVENTLOGWIDGET_H

#include <QDockWidget>

#include "ui_eventlogwidget.h"

namespace Ui {
class EventLogWidget;
}

class EventLogWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit EventLogWidget(QWidget *parent = nullptr);
    ~EventLogWidget() override;

    void reverseShow();

    void addTips(const QString &txt);

private:
    Ui::EventLogWidget *ui;
};

#endif // HUNT_EVENTLOGWIDGET_H
