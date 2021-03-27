#include "eventlogwidget.h"

#include <QDateTime>

EventLogWidget::EventLogWidget(QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::EventLogWidget)
{
    ui->setupUi(this);
    hide();
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    setAllowedAreas(Qt::AllDockWidgetAreas);
    setFloating(false);
    setWindowTitle(tr("event log"));
}

EventLogWidget::~EventLogWidget()
{
    delete ui;
}

void EventLogWidget::reverseShow()
{
    if (!isVisible()) {
        show();
        return;
    }
    hide();
}

void EventLogWidget::addTips(const QString &txt)
{
    auto time = QDateTime::currentDateTime().toString("hh:mm:ss");
    auto line = QString("[%2] %1\n").arg(txt, time);
    ui->plainTextEdit->appendPlainText(line);
}