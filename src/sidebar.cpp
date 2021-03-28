#include "sidebar.h"

#include <QDebug>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>

SideBar::SideBar(QWidget *parent)
    : QWidget(parent)
    , m_checkedAction(nullptr)
    , m_overAction(nullptr)
    , m_actionHeight(90)
{
    setMouseTracking(true);
}

void SideBar::paintEvent(QPaintEvent *event)
{
    QPainter p(this);

    QFont fontText(p.font());
    fontText.setFamily("Helvetica Neue");
    p.setFont(fontText);

    int action_y = 0;

    p.fillRect(rect(), QColor("#123456"));
    for (auto action : m_actions) {
        QRect actionRect(0, action_y, event->rect().width(), m_actionHeight);

        if (action->isChecked()) {
            p.fillRect(actionRect, QColor("#ffffff"));
        }

        if (action == m_overAction) {
            p.fillRect(actionRect, QColor("#fff333"));
        }

        p.setPen(QColor("#fff111"));
        QSize size = p.fontMetrics().size(Qt::TextSingleLine, action->text());
        QRect actionTextRect(QPoint(actionRect.width() / 2 - size.width() / 2,
                                    actionRect.bottom() - size.height() - 5),
                             size);
        p.drawText(actionTextRect, Qt::AlignCenter, action->text());

        QRect actionIconRect(0,
                             action_y + 10,
                             actionRect.width(),
                             actionRect.height() - 2 * actionTextRect.height() - 10);
        QIcon actionIcon(action->icon());
        actionIcon.paint(&p, actionIconRect);

        action_y += actionRect.height();
    }
}

QSize SideBar::minimumSizeHint() const
{
    return m_actionHeight * QSize(1, m_actions.size());
}

QAction *SideBar::addAction(const QString &text, const QIcon &icon)
{
    auto action = new QAction(icon, text, this);
    action->setCheckable(true);
    m_actions.push_back(action);
    update();
    return action;
}

void SideBar::mousePressEvent(QMouseEvent *event)
{
    QAction *tempAction = actionAt(event->pos());
    if (tempAction == nullptr || tempAction->isChecked()) {
        return;
    }
    if (m_checkedAction) {
        m_checkedAction->setChecked(false);
    }
    if (m_overAction == tempAction) {
        m_overAction = nullptr;
    }
    m_checkedAction = tempAction;
    tempAction->setChecked(true);
    update();
    QWidget::mousePressEvent(event);
}

void SideBar::mouseMoveEvent(QMouseEvent *event)
{
    QAction *tempAction = actionAt(event->pos());
    if (tempAction == nullptr) {
        m_overAction = nullptr;
        update();
        return;
    }
    if (tempAction->isChecked() || m_overAction == tempAction) {
        return;
    }
    m_overAction = tempAction;
    update();
    QWidget::mouseMoveEvent(event);
}

void SideBar::leaveEvent(QEvent *event)
{
    m_overAction = nullptr;
    update();
    QWidget::leaveEvent(event);
}

QAction *SideBar::actionAt(const QPoint &at)
{
    int action_y = 0;
    for (auto action : m_actions) {
        QRect actionRect(0, action_y, rect().width(), m_actionHeight);
        if (actionRect.contains(at)) {
            return action;
        }
        action_y += actionRect.height();
    }
    return nullptr;
}
