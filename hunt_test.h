#ifndef HUNT_TEST_H
#define HUNT_TEST_H

#include <QtTest/QtTest>

#if (defined(_WIN32) || defined(_WIN64))
#define HUNT_WIN
#else
#define HUNT_POSIX
#endif

namespace hunt {

class HuntTest : public QObject
{
    Q_OBJECT
private slots:
    void test_ScopeGuard_ExistOK();
    void test_Aria2Ctrl_ExistOK();
};

} // namespace hunt

#endif //HUNT_TEST_H
