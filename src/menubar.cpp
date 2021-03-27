#include "menubar.h"

MenuBar::MenuBar(QWidget *parent)
    : QMenuBar(parent)
    , m_menuFile(new QMenu{this})
    , m_actionOpen(new QAction{this})
{
    m_menuFile->setTitle(tr("file"));
    m_actionOpen->setText(tr("open"));

    addAction(m_menuFile->menuAction());
    m_menuFile->addAction(m_actionOpen);
}

MenuBar::~MenuBar() noexcept
{
    delete m_menuFile;
    delete m_actionOpen;
}