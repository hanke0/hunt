#ifndef HUNT_SCOPEGUARD_H
#define HUNT_SCOPEGUARD_H

#include <type_traits>
#include <utility>

namespace hunt {

template<typename FuncType>
class ScopeGuard
{
public:
    ScopeGuard() = delete;
    ScopeGuard(const ScopeGuard &) = default;
    ScopeGuard &operator=(const ScopeGuard &) = delete;
    void *operator new(std::size_t) = delete;
    ScopeGuard(FuncType &&f)
        : func_(f)
    {}
    ~ScopeGuard() { func_(); }

private:
    FuncType func_ = nullptr;
};

// internal used for the macro HUNT_ON_SCOPE_EXIT
enum class ScopeGuardFoo {};

template<typename FuncType>
ScopeGuard<FuncType> operator+(ScopeGuardFoo, FuncType &&rhs)
{
    return ScopeGuard<typename std::decay<FuncType>::type>(std::forward<FuncType>(rhs));
}

} // namespace hunt

#ifndef __COUNTER__
#define HUNT_ANONYMOUS_VARIABLE(s) s##__LINE__
#else
#define HUNT_ANONYMOUS_VARIABLE(s) s##__COUNTER__##__LINE__
#endif

/*
 * HUNT_ON_SCOPE_EXIT used for executing a function when leaving current scope.
 *
 * using example:
 * int foo(int a, int b) {
 *  int c;
 *  HUNT_ON_SCOPE_EXIT {
 *    // this line will print result after function end
 *    printf("I am leaving foo with result %d\n", c);
 *  }
 *  c = a + b;
 *  return c;
 * }
 *
 */
#define HUNT_ON_SCOPE_EXIT \
    auto HUNT_ANONYMOUS_VARIABLE(HUNT_SCOPE_EXIT_GUARD) = hunt::ScopeGuardFoo() + [&]() noexcept

#endif // HUNT_SCOPEGUARD_H
