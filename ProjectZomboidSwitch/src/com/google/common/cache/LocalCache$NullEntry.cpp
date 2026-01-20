#include <queue>
#include "com\google\common\cache/LocalCache$NullEntry.h"

namespace com {
namespace google {
namespace common {
namespace cache {

void LocalCache$NullEntry::setValueReference(Object> valueReference) {
    // TODO: Implement setValueReference
}

int LocalCache$NullEntry::getHash() {
    // TODO: Implement getHash
    return 0;
}

void* LocalCache$NullEntry::getKey() {
    // TODO: Implement getKey
    return nullptr;
}

long LocalCache$NullEntry::getAccessTime() {
    // TODO: Implement getAccessTime
    return 0;
}

void LocalCache$NullEntry::setAccessTime(long time) {
    // TODO: Implement setAccessTime
}

void LocalCache$NullEntry::setNextInAccessQueue(Object> next) {
    // TODO: Implement setNextInAccessQueue
}

void LocalCache$NullEntry::setPreviousInAccessQueue(Object> previous) {
    // TODO: Implement setPreviousInAccessQueue
}

long LocalCache$NullEntry::getWriteTime() {
    // TODO: Implement getWriteTime
    return 0;
}

void LocalCache$NullEntry::setWriteTime(long time) {
    // TODO: Implement setWriteTime
}

void LocalCache$NullEntry::setNextInWriteQueue(Object> next) {
    // TODO: Implement setNextInWriteQueue
}

void LocalCache$NullEntry::setPreviousInWriteQueue(Object> previous) {
    // TODO: Implement setPreviousInWriteQueue
}

} // namespace cache
} // namespace common
} // namespace google
} // namespace com
