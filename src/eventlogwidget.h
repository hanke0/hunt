#ifndef HUNT_EVENTLOGWIDGET_H
#define HUNT_EVENTLOGWIDGET_H

#include <QDockWidget>
#include <QGridLayout>
#include <QPlainTextEdit>

class EventLogWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit EventLogWidget(QWidget *parent = nullptr);
    ~EventLogWidget() override;

    void reverseShow();

    void addTips(const QString &txt);

private:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
};

#endif // HUNT_EVENTLOGWIDGET_H
