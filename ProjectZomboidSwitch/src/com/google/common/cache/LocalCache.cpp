#include <queue>
#include "com\google\common\cache/LocalCache.h"

namespace com {
namespace google {
namespace common {
namespace cache {

bool LocalCache::evictsBySize() {
    // TODO: Implement evictsBySize
    return false;
}

bool LocalCache::customWeigher() {
    // TODO: Implement customWeigher
    return false;
}

bool LocalCache::expires() {
    // TODO: Implement expires
    return false;
}

bool LocalCache::expiresAfterWrite() {
    // TODO: Implement expiresAfterWrite
    return false;
}

bool LocalCache::expiresAfterAccess() {
    // TODO: Implement expiresAfterAccess
    return false;
}

bool LocalCache::refreshes() {
    // TODO: Implement refreshes
    return false;
}

bool LocalCache::usesAccessQueue() {
    // TODO: Implement usesAccessQueue
    return false;
}

bool LocalCache::usesWriteQueue() {
    // TODO: Implement usesWriteQueue
    return false;
}

bool LocalCache::recordsWrite() {
    // TODO: Implement recordsWrite
    return false;
}

bool LocalCache::recordsAccess() {
    // TODO: Implement recordsAccess
    return false;
}

bool LocalCache::recordsTime() {
    // TODO: Implement recordsTime
    return false;
}

bool LocalCache::usesWriteEntries() {
    // TODO: Implement usesWriteEntries
    return false;
}

bool LocalCache::usesAccessEntries() {
    // TODO: Implement usesAccessEntries
    return false;
}

bool LocalCache::usesKeyReferences() {
    // TODO: Implement usesKeyReferences
    return false;
}

bool LocalCache::usesValueReferences() {
    // TODO: Implement usesValueReferences
    return false;
}

int LocalCache::rehash(int h) {
    // TODO: Implement rehash
    return 0;
}

int LocalCache::hash(@Nullable Object) {
    // TODO: Implement hash
    return 0;
}

return LocalCache::rehash() {
    // TODO: Implement rehash
    return nullptr;
}

void LocalCache::reclaimValue(V> valueReference) {
    // TODO: Implement reclaimValue
}

void LocalCache::reclaimKey(V> entry) {
    // TODO: Implement reclaimKey
}

bool LocalCache::isLive(V> entry, long now) {
    // TODO: Implement isLive
    return false;
}

V LocalCache::getLiveValue(V> entry, long now) {
    // TODO: Implement getLiveValue
    return nullptr;
}

bool LocalCache::isExpired(V> entry, long now) {
    // TODO: Implement isExpired
    return false;
}

void LocalCache::processPendingNotifications() {
    // TODO: Implement processPendingNotifications
}

void LocalCache::cleanUp() {
    // TODO: Implement cleanUp
}

bool LocalCache::isEmpty() {
    // TODO: Implement isEmpty
    return false;
}

long LocalCache::longSize() {
    // TODO: Implement longSize
    return 0;
}

int LocalCache::size() {
    // TODO: Implement size
    return 0;
}

V LocalCache::get(@Nullable Object) {
    // TODO: Implement get
    return nullptr;
}

V LocalCache::getIfPresent(void* key) {
    // TODO: Implement getIfPresent
    return nullptr;
}

V LocalCache::getOrDefault(@Nullable Object, @Nullable V) {
    // TODO: Implement getOrDefault
    return nullptr;
}

V LocalCache::get(K key, CacheLoader<? super, V> loader) {
    // TODO: Implement get
    return nullptr;
}

V LocalCache::getOrLoad(K key) {
    // TODO: Implement getOrLoad
    return nullptr;
}

void LocalCache::refresh(K key) {
    // TODO: Implement refresh
}

bool LocalCache::containsKey(@Nullable Object) {
    // TODO: Implement containsKey
    return false;
}

bool LocalCache::containsValue(@Nullable Object) {
    // TODO: Implement containsValue
    return false;
}

V LocalCache::put(K key, V value) {
    // TODO: Implement put
    return nullptr;
}

V LocalCache::putIfAbsent(K key, V value) {
    // TODO: Implement putIfAbsent
    return nullptr;
}

void LocalCache::putAll(Map<? extends, ? extends) {
    // TODO: Implement putAll
}

V LocalCache::remove(@Nullable Object) {
    // TODO: Implement remove
    return nullptr;
}

bool LocalCache::remove(@Nullable Object, @Nullable Object) {
    // TODO: Implement remove
    return false;
}

bool LocalCache::replace(K key, @Nullable V, V newValue) {
    // TODO: Implement replace
    return false;
}

V LocalCache::replace(K key, V value) {
    // TODO: Implement replace
    return nullptr;
}

void LocalCache::clear() {
    // TODO: Implement clear
}

void LocalCache::invalidateAll(Iterable<?> keys) {
    // TODO: Implement invalidateAll
}

} // namespace cache
} // namespace common
} // namespace google
} // namespace com
