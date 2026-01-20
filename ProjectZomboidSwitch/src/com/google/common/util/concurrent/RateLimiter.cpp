#include <string>
#include "com\google\common\util\concurrent/RateLimiter.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

RateLimiter RateLimiter::create(double permitsPerSecond) {
    // TODO: Implement create
    return nullptr;
}

return RateLimiter::create() {
    // TODO: Implement create
    return nullptr;
}

RateLimiter RateLimiter::create(SleepingStopwatch stopwatch, double permitsPerSecond) {
    // TODO: Implement create
    return nullptr;
}

RateLimiter RateLimiter::create(double permitsPerSecond, long warmupPeriod, TimeUnit unit) {
    // TODO: Implement create
    return nullptr;
}

return RateLimiter::create() {
    // TODO: Implement create
    return nullptr;
}

RateLimiter RateLimiter::create(SleepingStopwatch stopwatch, double permitsPerSecond, long warmupPeriod, TimeUnit unit, double coldFactor) {
    // TODO: Implement create
    return nullptr;
}

void* RateLimiter::mutex() {
    // TODO: Implement mutex
    return nullptr;
}

void RateLimiter::setRate(double permitsPerSecond) {
    // TODO: Implement setRate
}

double RateLimiter::getRate() {
    // TODO: Implement getRate
    return 0;
}

double RateLimiter::acquire() {
    // TODO: Implement acquire
    return 0;
}

double RateLimiter::acquire(int permits) {
    // TODO: Implement acquire
    return 0;
}

long RateLimiter::reserve(int permits) {
    // TODO: Implement reserve
    return 0;
}

bool RateLimiter::tryAcquire(long timeout, TimeUnit unit) {
    // TODO: Implement tryAcquire
    return false;
}

bool RateLimiter::tryAcquire(int permits) {
    // TODO: Implement tryAcquire
    return false;
}

bool RateLimiter::tryAcquire() {
    // TODO: Implement tryAcquire
    return false;
}

bool RateLimiter::tryAcquire(int permits, long timeout, TimeUnit unit) {
    // TODO: Implement tryAcquire
    return false;
}

bool RateLimiter::canAcquire(long nowMicros, long timeoutMicros) {
    // TODO: Implement canAcquire
    return false;
}

long RateLimiter::reserveAndGetWaitLength(int permits, long nowMicros) {
    // TODO: Implement reserveAndGetWaitLength
    return 0;
}

std::string RateLimiter::toString() {
    // TODO: Implement toString
    return "";
}

void RateLimiter::checkPermits(int permits) {
    // TODO: Implement checkPermits
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
