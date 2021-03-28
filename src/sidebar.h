//
// Created by kehan on 2021/3/28.
//

#ifndef HUNT_SIDEBAR_H
#define HUNT_SIDEBAR_H

#include <QAbstractSocket>
#include <QAction>
#include <QWidget>

class SideBar : public QWidget
{
    Q_OBJECT
public:
    explicit SideBar(QWidget *parent = nullptr);
    QAction *addAction(const QString &text, const QIcon &icon = QIcon());
    QSize minimumSizeHint() const override;

    void setActionHeight(int h) { m_actionHeight = h; }

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;

    QAction *actionAt(const QPoint &at);

private:
    QList<QAction *> m_actions;

    QAction *m_checkedAction;
    QAction *m_overAction;
    int m_actionHeight;
};

#endif //SIDEBAR_H
