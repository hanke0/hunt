#include "mainwindow.h"
#include "aria2ctrl.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_ariaProcess(new hunt::Aria2Ctrl{this})
    , m_ariaLabel(new QLabel{this})
    , m_ariaClient(new hunt::Aria2Client{this})
    , m_eventLogWidget(new EventLogWidget{this})
    , m_eventLogButton(new QPushButton{this})
{
    ui->setupUi(this);
    ui->statusbar->addWidget(m_ariaLabel);
    setupStatusBarEventLog();
    setupAria();
}

MainWindow::~MainWindow()
{
    delete m_ariaProcess;
    delete m_ariaClient;
    delete ui;
}

void MainWindow::setupAria()
{
    connect(m_ariaProcess->m_aria2c,
            &QProcess::stateChanged,
            this,
            [this](QProcess::ProcessState state) {
                auto tips = QString("aria2c change state %1").arg(QtEnumToQString(state));
                this->m_eventLogWidget->addTips(tips);
                if (state != QProcess::ProcessState::Running) {
                    this->m_ariaLabel->setText(tr("aria2c is not running!"));
                    return;
                }
            });
    connect(m_ariaClient,
            &hunt::Aria2Client::ariaConnectionStateChange,
            this,
            &MainWindow::on_ariaConnectionStateChange);
    m_ariaProcess->start();
    m_ariaClient->setPort(m_ariaProcess->m_port);
    m_ariaClient->openConnect();
}

void MainWindow::setupStatusBarEventLog()
{
    m_eventLogButton->setFlat(true);
    m_eventLogButton->setStyleSheet("margin:0;hover{background-color: grey;}");
    m_eventLogButton->setText(tr("event log"));
    ui->statusbar->addPermanentWidget(m_eventLogButton);
    addDockWidget(Qt::BottomDockWidgetArea, m_eventLogWidget);
    connect(m_eventLogButton, &QPushButton::clicked, this, [this] {
        this->m_eventLogWidget->reverseShow();
    });
}

void MainWindow::on_ariaConnectionStateChange(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::ConnectedState) {
        m_ariaLabel->setText(tr("aria2 connected"));
    } else {
        m_ariaLabel->setText(tr("aria2 disconnected"));
    }
    auto tips = QString("aria2 connection state changed %1").arg(QtEnumToQString(state));
    m_eventLogWidget->addTips(tips);
}
