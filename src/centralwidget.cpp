#include <QAction>
#include <QHBoxLayout>
#include <QIcon>

#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
    , sidebar(new SideBar{this})
    , stackedWidget(new QStackedWidget{this})
{
    setParent(parent);
    auto style = new QHBoxLayout{this};
    sidebar->addAction(tr("download list"), QIcon(":/icons/hunt.png"));
    style->addWidget(sidebar);
    style->addWidget(stackedWidget);
    style->setMargin(0);
}

void CentralWidget::setUp(QMainWindow *mainWindow)
{
    mainWindow->setCentralWidget(this);
}