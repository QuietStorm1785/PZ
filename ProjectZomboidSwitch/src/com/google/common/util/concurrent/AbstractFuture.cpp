#include <string>
#include "com\google\common\util\concurrent/AbstractFuture.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

void AbstractFuture::removeWaiter(Waiter node) {
    // TODO: Implement removeWaiter
}

protected AbstractFuture::AbstractFuture() {
    // TODO: Implement AbstractFuture
    return nullptr;
}

V AbstractFuture::get(long timeout, TimeUnit unit) {
    // TODO: Implement get
    return nullptr;
}

V AbstractFuture::get() {
    // TODO: Implement get
    return nullptr;
}

V AbstractFuture::getDoneValue(void* obj) {
    // TODO: Implement getDoneValue
    return nullptr;
}

throw AbstractFuture::cancellationExceptionWithCause("Task was) {
    // TODO: Implement cancellationExceptionWithCause
    return nullptr;
}

bool AbstractFuture::isDone() {
    // TODO: Implement isDone
    return false;
}

bool AbstractFuture::isCancelled() {
    // TODO: Implement isCancelled
    return false;
}

bool AbstractFuture::cancel(bool mayInterruptIfRunning) {
    // TODO: Implement cancel
    return false;
}

void AbstractFuture::interruptTask() {
    // TODO: Implement interruptTask
}

bool AbstractFuture::wasInterrupted() {
    // TODO: Implement wasInterrupted
    return false;
}

void AbstractFuture::addListener(Runnable listener, Executor executor) {
    // TODO: Implement addListener
}

bool AbstractFuture::set(@Nullable V) {
    // TODO: Implement set
    return false;
}

bool AbstractFuture::setException(std::exception throwable) {
    // TODO: Implement setException
    return false;
}

bool AbstractFuture::setFuture(ListenableFuture<? extends) {
    // TODO: Implement setFuture
    return false;
}

void* AbstractFuture::getFutureValue(ListenableFuture<?> future) {
    // TODO: Implement getFutureValue
    return nullptr;
}

void AbstractFuture::complete(AbstractFuture<?> future) {
    // TODO: Implement complete
}

void AbstractFuture::afterDone() {
    // TODO: Implement afterDone
}

std::exception AbstractFuture::trustedGetException() {
    // TODO: Implement trustedGetException
    return nullptr;
}

void AbstractFuture::maybePropagateCancellation(@Nullable Future<?>) {
    // TODO: Implement maybePropagateCancellation
}

void AbstractFuture::releaseWaiters() {
    // TODO: Implement releaseWaiters
}

Listener AbstractFuture::clearListeners(Listener onto) {
    // TODO: Implement clearListeners
    return nullptr;
}

void AbstractFuture::executeListener(Runnable runnable, Executor executor) {
    // TODO: Implement executeListener
}

CancellationException AbstractFuture::cancellationExceptionWithCause(@Nullable std::string, @Nullable Throwable) {
    // TODO: Implement cancellationExceptionWithCause
    return nullptr;
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
