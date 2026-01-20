#include "com\google\common\cache/LocalCache$LoadingValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {

bool LocalCache$LoadingValueReference::isLoading() {
    // TODO: Implement isLoading
    return false;
}

bool LocalCache$LoadingValueReference::isActive() {
    // TODO: Implement isActive
    return false;
}

int LocalCache$LoadingValueReference::getWeight() {
    // TODO: Implement getWeight
    return 0;
}

bool LocalCache$LoadingValueReference::set(@Nullable V) {
    // TODO: Implement set
    return false;
}

bool LocalCache$LoadingValueReference::setException(std::exception t) {
    // TODO: Implement setException
    return false;
}

void LocalCache$LoadingValueReference::notifyNewValue(@Nullable V) {
    // TODO: Implement notifyNewValue
}

long LocalCache$LoadingValueReference::elapsedNanos() {
    // TODO: Implement elapsedNanos
    return 0;
}

V LocalCache$LoadingValueReference::waitForValue() {
    // TODO: Implement waitForValue
    return nullptr;
}

V LocalCache$LoadingValueReference::get() {
    // TODO: Implement get
    return nullptr;
}

} // namespace cache
} // namespace common
} // namespace google
} // namespace com
