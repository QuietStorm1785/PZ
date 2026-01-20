#include "com\google\common\util\concurrent/SmoothRateLimiter.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

private SmoothRateLimiter::SmoothRateLimiter(SleepingStopwatch stopwatch) {
    // TODO: Implement SmoothRateLimiter
    return nullptr;
}

void SmoothRateLimiter::doSetRate(double permitsPerSecond, long nowMicros) {
    // TODO: Implement doSetRate
}

double SmoothRateLimiter::doGetRate() {
    // TODO: Implement doGetRate
    return 0;
}

long SmoothRateLimiter::queryEarliestAvailable(long nowMicros) {
    // TODO: Implement queryEarliestAvailable
    return 0;
}

long SmoothRateLimiter::reserveEarliestAvailable(int requiredPermits, long nowMicros) {
    // TODO: Implement reserveEarliestAvailable
    return 0;
}

void SmoothRateLimiter::resync(long nowMicros) {
    // TODO: Implement resync
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
