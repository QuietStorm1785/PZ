#include <queue>
#include "com\google\common\util\concurrent/ForwardingBlockingQueue.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

protected ForwardingBlockingQueue::ForwardingBlockingQueue() {
    // TODO: Implement ForwardingBlockingQueue
    return nullptr;
}

int ForwardingBlockingQueue::drainTo(Collection<? super, int maxElements) {
    // TODO: Implement drainTo
    return 0;
}

int ForwardingBlockingQueue::drainTo(Collection<? super) {
    // TODO: Implement drainTo
    return 0;
}

bool ForwardingBlockingQueue::offer(E e, long timeout, TimeUnit unit) {
    // TODO: Implement offer
    return false;
}

E ForwardingBlockingQueue::poll(long timeout, TimeUnit unit) {
    // TODO: Implement poll
    return nullptr;
}

void ForwardingBlockingQueue::put(E e) {
    // TODO: Implement put
}

int ForwardingBlockingQueue::remainingCapacity() {
    // TODO: Implement remainingCapacity
    return 0;
}

E ForwardingBlockingQueue::take() {
    // TODO: Implement take
    return nullptr;
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
