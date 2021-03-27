#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QMainWindow>
#include <QWidget>

class CentralWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr);
    ~CentralWidget() noexcept override = default;

    void setUp(QMainWindow *mainWindow);
};

#endif //CENTRALWIDGET_H
