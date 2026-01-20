#include "com\google\common\collect/ForwardingBlockingDeque.h"

namespace com {
namespace google {
namespace common {
namespace collect {

protected ForwardingBlockingDeque::ForwardingBlockingDeque() {
    // TODO: Implement ForwardingBlockingDeque
    return nullptr;
}

int ForwardingBlockingDeque::remainingCapacity() {
    // TODO: Implement remainingCapacity
    return 0;
}

void ForwardingBlockingDeque::putFirst(E e) {
    // TODO: Implement putFirst
}

void ForwardingBlockingDeque::putLast(E e) {
    // TODO: Implement putLast
}

bool ForwardingBlockingDeque::offerFirst(E e, long timeout, TimeUnit unit) {
    // TODO: Implement offerFirst
    return false;
}

bool ForwardingBlockingDeque::offerLast(E e, long timeout, TimeUnit unit) {
    // TODO: Implement offerLast
    return false;
}

E ForwardingBlockingDeque::takeFirst() {
    // TODO: Implement takeFirst
    return nullptr;
}

E ForwardingBlockingDeque::takeLast() {
    // TODO: Implement takeLast
    return nullptr;
}

E ForwardingBlockingDeque::pollFirst(long timeout, TimeUnit unit) {
    // TODO: Implement pollFirst
    return nullptr;
}

E ForwardingBlockingDeque::pollLast(long timeout, TimeUnit unit) {
    // TODO: Implement pollLast
    return nullptr;
}

void ForwardingBlockingDeque::put(E e) {
    // TODO: Implement put
}

bool ForwardingBlockingDeque::offer(E e, long timeout, TimeUnit unit) {
    // TODO: Implement offer
    return false;
}

E ForwardingBlockingDeque::take() {
    // TODO: Implement take
    return nullptr;
}

E ForwardingBlockingDeque::poll(long timeout, TimeUnit unit) {
    // TODO: Implement poll
    return nullptr;
}

int ForwardingBlockingDeque::drainTo(Collection<? super) {
    // TODO: Implement drainTo
    return 0;
}

int ForwardingBlockingDeque::drainTo(Collection<? super, int maxElements) {
    // TODO: Implement drainTo
    return 0;
}

} // namespace collect
} // namespace common
} // namespace google
} // namespace com
