#include "eventlogwidget.h"

#include <QDateTime>

EventLogWidget::EventLogWidget(QWidget *parent)
    : QDockWidget(parent)
    , dockWidgetContents(new QWidget{this})
    , gridLayout(new QGridLayout{dockWidgetContents})
    , plainTextEdit(new QPlainTextEdit{dockWidgetContents})
{
    gridLayout->setMargin(0);
    gridLayout->addWidget(plainTextEdit, 0, 0);
    dockWidgetContents->setLayout(gridLayout);
    setWidget(dockWidgetContents);

    hide();
    setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetClosable);
    setAllowedAreas(Qt::AllDockWidgetAreas);
    setFloating(false);
    setWindowTitle(tr("event log"));
}

EventLogWidget::~EventLogWidget()
{
    delete plainTextEdit;
    delete gridLayout;
    delete dockWidgetContents;
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
    plainTextEdit->appendPlainText(line);
}