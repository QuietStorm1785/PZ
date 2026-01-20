#include "com\google\common\util\concurrent/ImmediateFuture.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

void ImmediateFuture::addListener(Runnable listener, Executor executor) {
    // TODO: Implement addListener
}

bool ImmediateFuture::cancel(bool mayInterruptIfRunning) {
    // TODO: Implement cancel
    return false;
}

V ImmediateFuture::get(long timeout, TimeUnit unit) {
    // TODO: Implement get
    return nullptr;
}

bool ImmediateFuture::isCancelled() {
    // TODO: Implement isCancelled
    return false;
}

bool ImmediateFuture::isDone() {
    // TODO: Implement isDone
    return false;
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
