#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_statusbar(new StatusBar{this})
    , m_menubar(new MenuBar{this})
    , m_centralWidget(new CentralWidget{this})
{
    resize(800, 600);
    setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    setAnimated(true);
    setDocumentMode(false);
    setWindowTitle(tr("Hunt Download Tool"));

    m_menubar->setGeometry(QRect(0, 0, 800, 24));
    setMenuBar(m_menubar);

    m_statusbar->setUp(this);
    setStatusBar(m_statusbar);

    m_centralWidget->setUp(this);
}

MainWindow::~MainWindow() noexcept
{
    delete m_menubar;
    delete m_statusbar;
}
