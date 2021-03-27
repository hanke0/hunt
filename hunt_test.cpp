#include "hunt_test.h"

#include "aria2ctrl.h"
#include "scopeguard.h"

#if defined(HUNT_POSIX)
#include <signal.h>
#endif

namespace hunt {

static bool isProcessRunning(qint64 pid)
{
#if defined(HUNT_POSIX)
    if (pid <= 0) {
        return false;
    }
    return kill(pid, 0) == 0;
#else
    return true;
#endif
}

void HuntTest::test_ScopeGuard_ExistOK()
{
    int a = 0;
    {
        HUNT_ON_SCOPE_EXIT { a = 1; };
    }
    QCOMPARE(1, a);
}

void HuntTest::test_Aria2Ctrl_ExistOK()
{
    Aria2Ctrl aria;
    Q_ASSERT(!aria.running());
    aria.start(true);
    Q_ASSERT(aria.running());
    auto pid = aria.pid();
    QCOMPARE(true, isProcessRunning(pid));
    aria.terminate(true);
    QCOMPARE(false, isProcessRunning(pid));
}

} // namespace hunt

QTEST_MAIN(hunt::HuntTest)
