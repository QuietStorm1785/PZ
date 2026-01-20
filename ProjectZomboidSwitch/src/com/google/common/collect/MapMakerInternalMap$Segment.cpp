#include <queue>
#include "com\google\common\collect/MapMakerInternalMap$Segment.h"

namespace com {
namespace google {
namespace common {
namespace collect {

void MapMakerInternalMap$Segment::maybeDrainReferenceQueues() {
    // TODO: Implement maybeDrainReferenceQueues
}

void MapMakerInternalMap$Segment::maybeClearReferenceQueues() {
    // TODO: Implement maybeClearReferenceQueues
}

void MapMakerInternalMap$Segment::setValue(E entry, V value) {
    // TODO: Implement setValue
}

E MapMakerInternalMap$Segment::copyEntry(E original, E newNext) {
    // TODO: Implement copyEntry
    return nullptr;
}

void MapMakerInternalMap$Segment::initTable(AtomicReferenceArray<E> newTable) {
    // TODO: Implement initTable
}

void MapMakerInternalMap$Segment::setWeakValueReferenceForTesting(?> entry, ? extends, ?>> valueReference) {
    // TODO: Implement setWeakValueReferenceForTesting
}

void MapMakerInternalMap$Segment::setTableEntryForTesting(int i, ?> entry) {
    // TODO: Implement setTableEntryForTesting
}

E MapMakerInternalMap$Segment::copyForTesting(?> entry, @Nullable InternalEntry<K, ?> newNext) {
    // TODO: Implement copyForTesting
    return nullptr;
}

void MapMakerInternalMap$Segment::setValueForTesting(?> entry, V value) {
    // TODO: Implement setValueForTesting
}

E MapMakerInternalMap$Segment::newEntryForTesting(K key, int hash, @Nullable InternalEntry<K, ?> next) {
    // TODO: Implement newEntryForTesting
    return nullptr;
}

bool MapMakerInternalMap$Segment::removeTableEntryForTesting(?> entry) {
    // TODO: Implement removeTableEntryForTesting
    return false;
}

E MapMakerInternalMap$Segment::removeFromChainForTesting(?> first, ?> entry) {
    // TODO: Implement removeFromChainForTesting
    return nullptr;
}

V MapMakerInternalMap$Segment::getLiveValueForTesting(?> entry) {
    // TODO: Implement getLiveValueForTesting
    return nullptr;
}

void MapMakerInternalMap$Segment::tryDrainReferenceQueues() {
    // TODO: Implement tryDrainReferenceQueues
}

void MapMakerInternalMap$Segment::drainKeyReferenceQueue(ReferenceQueue<K> keyReferenceQueue) {
    // TODO: Implement drainKeyReferenceQueue
}

void MapMakerInternalMap$Segment::drainValueReferenceQueue(ReferenceQueue<V> valueReferenceQueue) {
    // TODO: Implement drainValueReferenceQueue
}

E MapMakerInternalMap$Segment::getFirst(int hash) {
    // TODO: Implement getFirst
    return nullptr;
}

E MapMakerInternalMap$Segment::getEntry(void* key, int hash) {
    // TODO: Implement getEntry
    return nullptr;
}

E MapMakerInternalMap$Segment::getLiveEntry(void* key, int hash) {
    // TODO: Implement getLiveEntry
    return nullptr;
}

V MapMakerInternalMap$Segment::get(void* key, int hash) {
    // TODO: Implement get
    return nullptr;
}

bool MapMakerInternalMap$Segment::containsKey(void* key, int hash) {
    // TODO: Implement containsKey
    return false;
}

bool MapMakerInternalMap$Segment::containsValue(void* value) {
    // TODO: Implement containsValue
    return false;
}

V MapMakerInternalMap$Segment::put(K key, int hash, V value, bool onlyIfAbsent) {
    // TODO: Implement put
    return nullptr;
}

void MapMakerInternalMap$Segment::expand() {
    // TODO: Implement expand
}

bool MapMakerInternalMap$Segment::replace(K key, int hash, V oldValue, V newValue) {
    // TODO: Implement replace
    return false;
}

V MapMakerInternalMap$Segment::replace(K key, int hash, V newValue) {
    // TODO: Implement replace
    return nullptr;
}

V MapMakerInternalMap$Segment::remove(void* key, int hash) {
    // TODO: Implement remove
    return nullptr;
}

bool MapMakerInternalMap$Segment::remove(void* key, int hash, void* value) {
    // TODO: Implement remove
    return false;
}

void MapMakerInternalMap$Segment::clear() {
    // TODO: Implement clear
}

E MapMakerInternalMap$Segment::removeFromChain(E first, E entry) {
    // TODO: Implement removeFromChain
    return nullptr;
}

bool MapMakerInternalMap$Segment::reclaimKey(E entry, int hash) {
    // TODO: Implement reclaimKey
    return false;
}

bool MapMakerInternalMap$Segment::reclaimValue(K key, int hash, E> valueReference) {
    // TODO: Implement reclaimValue
    return false;
}

bool MapMakerInternalMap$Segment::clearValueForTesting(K key, int hash, ? extends, ?>> valueReference) {
    // TODO: Implement clearValueForTesting
    return false;
}

bool MapMakerInternalMap$Segment::removeEntryForTesting(E entry) {
    // TODO: Implement removeEntryForTesting
    return false;
}

V MapMakerInternalMap$Segment::getLiveValue(E entry) {
    // TODO: Implement getLiveValue
    return nullptr;
}

void MapMakerInternalMap$Segment::postReadCleanup() {
    // TODO: Implement postReadCleanup
}

void MapMakerInternalMap$Segment::preWriteCleanup() {
    // TODO: Implement preWriteCleanup
}

void MapMakerInternalMap$Segment::runCleanup() {
    // TODO: Implement runCleanup
}

void MapMakerInternalMap$Segment::runLockedCleanup() {
    // TODO: Implement runLockedCleanup
}

} // namespace collect
} // namespace common
} // namespace google
} // namespace com
