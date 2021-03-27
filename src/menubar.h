#ifndef HUNT_MENUBAR_H
#define HUNT_MENUBAR_H

#include <QAction>
#include <QMenu>
#include <QMenuBar>

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(QObject *parent);
    ~MenuBar() noexcept override;

public:
    QMenu *m_menuFile;
    QAction *m_actionOpen;
};

#endif //HUNT_MENUBAR_H
