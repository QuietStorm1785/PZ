#include "com/google/common/eventbus/Subscriber.h"

namespace com {
namespace google {
namespace common {
namespace eventbus {

Subscriber Subscriber::create(EventBus bus, void* listener, Method method) {
    // TODO: Implement create
    return nullptr;
}

private Subscriber::Subscriber(EventBus bus, void* target, Method method) {
    // TODO: Implement Subscriber
    return nullptr;
}

void Subscriber::dispatchEvent(void* event) {
    // TODO: Implement dispatchEvent
}

void Subscriber::invokeSubscriberMethod(void* event) {
    // TODO: Implement invokeSubscriberMethod
}

SubscriberExceptionContext Subscriber::context(void* event) {
    // TODO: Implement context
    return nullptr;
}

int Subscriber::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

bool Subscriber::equals(@Nullable Object) {
    // TODO: Implement equals
    return false;
}

bool Subscriber::isDeclaredThreadSafe(Method method) {
    // TODO: Implement isDeclaredThreadSafe
    return false;
}

} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
