#include "statusbar.h"

StatusBar::StatusBar(QObject *parent)
    : m_ariaProcess(new hunt::Aria2Ctrl{this})
    , m_ariaLabel(new QLabel{this})
    , m_ariaClient(new hunt::Aria2Client{this})
    , m_eventLogWidget(new EventLogWidget{this})
    , m_eventLogButton(new QPushButton{this})
{
    setStyleSheet(QString::fromUtf8("margin-left: 10;"
                                    "margin-right: 10;"));
}

StatusBar::~StatusBar()
{
    delete m_ariaClient;
    delete m_ariaProcess;

    delete m_eventLogButton;
    delete m_eventLogWidget;
    delete m_ariaLabel;
}

void StatusBar::setUp(QMainWindow *mainWindow)
{
    setupStatusBarEventLog(mainWindow);
    setupAria();
}

void StatusBar::setupAria()
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
            &StatusBar::on_ariaConnectionStateChange);
    m_ariaProcess->start();
    m_ariaClient->setPort(m_ariaProcess->m_port);
    m_ariaClient->openConnect();
}

void StatusBar::setupStatusBarEventLog(QMainWindow *mainWindow)
{
    m_eventLogButton->setFlat(true);
    m_eventLogButton->setStyleSheet("margin:0;hover{background-color: grey;}");
    m_eventLogButton->setText(tr("event log"));
    addPermanentWidget(m_eventLogButton);
    mainWindow->addDockWidget(Qt::BottomDockWidgetArea, m_eventLogWidget);
    connect(m_eventLogButton, &QPushButton::clicked, this, [this] {
        this->m_eventLogWidget->reverseShow();
    });
}

void StatusBar::on_ariaConnectionStateChange(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::ConnectedState) {
        m_ariaLabel->setText(tr("aria2 connected"));
    } else {
        m_ariaLabel->setText(tr("aria2 disconnected"));
    }
    auto tips = QString("aria2 connection state changed %1").arg(QtEnumToQString(state));
    m_eventLogWidget->addTips(tips);
}