#include <queue>
#include "com\google\common\cache/LocalCache$Segment.h"

namespace com {
namespace google {
namespace common {
namespace cache {

void LocalCache$Segment::initTable(V>> newTable) {
    // TODO: Implement initTable
}

void LocalCache$Segment::setValue(V> entry, K key, V value, long now) {
    // TODO: Implement setValue
}

V LocalCache$Segment::get(K key, int hash, CacheLoader<? super, V> loader) {
    // TODO: Implement get
    return nullptr;
}

V LocalCache$Segment::lockedGetOrLoad(K key, int hash, CacheLoader<? super, V> loader) {
    // TODO: Implement lockedGetOrLoad
    return nullptr;
}

V LocalCache$Segment::waitForLoadingValue(V> e, K key, V> valueReference) {
    // TODO: Implement waitForLoadingValue
    return nullptr;
}

V LocalCache$Segment::loadSync(K key, int hash, V> loadingValueReference, CacheLoader<? super, V> loader) {
    // TODO: Implement loadSync
    return nullptr;
}

V LocalCache$Segment::getAndRecordStats(K key, int hash, V> loadingValueReference, ListenableFuture<V> newValue) {
    // TODO: Implement getAndRecordStats
    return nullptr;
}

V LocalCache$Segment::scheduleRefresh(V> entry, K key, int hash, V oldValue, long now, CacheLoader<? super, V> loader) {
    // TODO: Implement scheduleRefresh
    return nullptr;
}

V LocalCache$Segment::refresh(K key, int hash, CacheLoader<? super, V> loader, bool checkTime) {
    // TODO: Implement refresh
    return nullptr;
}

void LocalCache$Segment::tryDrainReferenceQueues() {
    // TODO: Implement tryDrainReferenceQueues
}

void LocalCache$Segment::drainReferenceQueues() {
    // TODO: Implement drainReferenceQueues
}

void LocalCache$Segment::drainKeyReferenceQueue() {
    // TODO: Implement drainKeyReferenceQueue
}

void LocalCache$Segment::drainValueReferenceQueue() {
    // TODO: Implement drainValueReferenceQueue
}

void LocalCache$Segment::clearReferenceQueues() {
    // TODO: Implement clearReferenceQueues
}

void LocalCache$Segment::clearKeyReferenceQueue() {
    // TODO: Implement clearKeyReferenceQueue
}

void LocalCache$Segment::clearValueReferenceQueue() {
    // TODO: Implement clearValueReferenceQueue
}

void LocalCache$Segment::recordRead(V> entry, long now) {
    // TODO: Implement recordRead
}

void LocalCache$Segment::recordLockedRead(V> entry, long now) {
    // TODO: Implement recordLockedRead
}

void LocalCache$Segment::recordWrite(V> entry, int weight, long now) {
    // TODO: Implement recordWrite
}

void LocalCache$Segment::drainRecencyQueue() {
    // TODO: Implement drainRecencyQueue
}

void LocalCache$Segment::tryExpireEntries(long now) {
    // TODO: Implement tryExpireEntries
}

void LocalCache$Segment::expireEntries(long now) {
    // TODO: Implement expireEntries
}

void LocalCache$Segment::enqueueNotification(@Nullable K, int hash, @Nullable V, int weight, RemovalCause cause) {
    // TODO: Implement enqueueNotification
}

void LocalCache$Segment::evictEntries(V> newest) {
    // TODO: Implement evictEntries
}

V LocalCache$Segment::getLiveValue(V> entry, long now) {
    // TODO: Implement getLiveValue
    return nullptr;
}

V LocalCache$Segment::get(void* key, int hash) {
    // TODO: Implement get
    return nullptr;
}

bool LocalCache$Segment::containsKey(void* key, int hash) {
    // TODO: Implement containsKey
    return false;
}

bool LocalCache$Segment::containsValue(void* value) {
    // TODO: Implement containsValue
    return false;
}

V LocalCache$Segment::put(K key, int hash, V value, bool onlyIfAbsent) {
    // TODO: Implement put
    return nullptr;
}

void LocalCache$Segment::expand() {
    // TODO: Implement expand
}

bool LocalCache$Segment::replace(K key, int hash, V oldValue, V newValue) {
    // TODO: Implement replace
    return false;
}

V LocalCache$Segment::replace(K key, int hash, V newValue) {
    // TODO: Implement replace
    return nullptr;
}

V LocalCache$Segment::remove(void* key, int hash) {
    // TODO: Implement remove
    return nullptr;
}

bool LocalCache$Segment::storeLoadedValue(K key, int hash, V> oldValueReference, V newValue) {
    // TODO: Implement storeLoadedValue
    return false;
}

bool LocalCache$Segment::remove(void* key, int hash, void* value) {
    // TODO: Implement remove
    return false;
}

void LocalCache$Segment::clear() {
    // TODO: Implement clear
}

void LocalCache$Segment::removeCollectedEntry(V> entry) {
    // TODO: Implement removeCollectedEntry
}

bool LocalCache$Segment::reclaimKey(V> entry, int hash) {
    // TODO: Implement reclaimKey
    return false;
}

bool LocalCache$Segment::reclaimValue(K key, int hash, V> valueReference) {
    // TODO: Implement reclaimValue
    return false;
}

bool LocalCache$Segment::removeLoadingValue(K key, int hash, V> valueReference) {
    // TODO: Implement removeLoadingValue
    return false;
}

bool LocalCache$Segment::removeEntry(V> entry, int hash, RemovalCause cause) {
    // TODO: Implement removeEntry
    return false;
}

void LocalCache$Segment::postReadCleanup() {
    // TODO: Implement postReadCleanup
}

void LocalCache$Segment::preWriteCleanup(long now) {
    // TODO: Implement preWriteCleanup
}

void LocalCache$Segment::postWriteCleanup() {
    // TODO: Implement postWriteCleanup
}

void LocalCache$Segment::cleanUp() {
    // TODO: Implement cleanUp
}

void LocalCache$Segment::runLockedCleanup(long now) {
    // TODO: Implement runLockedCleanup
}

void LocalCache$Segment::runUnlockedCleanup() {
    // TODO: Implement runUnlockedCleanup
}

} // namespace cache
} // namespace common
} // namespace google
} // namespace com
