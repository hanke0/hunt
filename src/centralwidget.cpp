//
// Created by kehan on 2021/3/28.
//

#include "centralwidget.h"

CentralWidget::CentralWidget(QWidget *parent)
    : QWidget(parent)
{
    setParent(parent);
}

void CentralWidget::setUp(QMainWindow *mainWindow)
{
    mainWindow->setCentralWidget(this);
}