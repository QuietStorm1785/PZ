#include "com\google\common\collect/AbstractBiMap.h"

namespace com {
namespace google {
namespace common {
namespace collect {

private AbstractBiMap::AbstractBiMap(V> backward, K> forward) {
    // TODO: Implement AbstractBiMap
    return nullptr;
}

K AbstractBiMap::checkKey(@Nullable K) {
    // TODO: Implement checkKey
    return nullptr;
}

V AbstractBiMap::checkValue(@Nullable V) {
    // TODO: Implement checkValue
    return nullptr;
}

void AbstractBiMap::setDelegates(V> forward, K> backward) {
    // TODO: Implement setDelegates
}

void AbstractBiMap::setInverse(K> inverse) {
    // TODO: Implement setInverse
}

bool AbstractBiMap::containsValue(@Nullable Object) {
    // TODO: Implement containsValue
    return false;
}

V AbstractBiMap::put(@Nullable K, @Nullable V) {
    // TODO: Implement put
    return nullptr;
}

V AbstractBiMap::forcePut(@Nullable K, @Nullable V) {
    // TODO: Implement forcePut
    return nullptr;
}

V AbstractBiMap::putInBothMaps(@Nullable K, @Nullable V, bool force) {
    // TODO: Implement putInBothMaps
    return nullptr;
}

void AbstractBiMap::updateInverseMap(K key, bool containedKey, V oldValue, V newValue) {
    // TODO: Implement updateInverseMap
}

V AbstractBiMap::remove(@Nullable Object) {
    // TODO: Implement remove
    return nullptr;
}

V AbstractBiMap::removeFromBothMaps(void* key) {
    // TODO: Implement removeFromBothMaps
    return nullptr;
}

void AbstractBiMap::removeFromInverseMap(V oldValue) {
    // TODO: Implement removeFromInverseMap
}

void AbstractBiMap::putAll(Map<? extends, ? extends) {
    // TODO: Implement putAll
}

void AbstractBiMap::clear() {
    // TODO: Implement clear
}

} // namespace collect
} // namespace common
} // namespace google
} // namespace com
