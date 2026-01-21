#include "com/google/common/cache/AbstractCache.h"

namespace com {
namespace google {
namespace common {
namespace cache {

protected AbstractCache::AbstractCache() {
    // TODO: Implement AbstractCache
    return nullptr;
}

V AbstractCache::get(K key, Callable<? extends) {
    // TODO: Implement get
    return nullptr;
}

void AbstractCache::put(K key, V value) {
    // TODO: Implement put
}

void AbstractCache::putAll(Map<? extends, ? extends) {
    // TODO: Implement putAll
}

void AbstractCache::cleanUp() {
    // TODO: Implement cleanUp
}

long AbstractCache::size() {
    // TODO: Implement size
    return 0;
}

void AbstractCache::invalidate(void* key) {
    // TODO: Implement invalidate
}

void AbstractCache::invalidateAll(Iterable<?> keys) {
    // TODO: Implement invalidateAll
}

void AbstractCache::invalidateAll() {
    // TODO: Implement invalidateAll
}

CacheStats AbstractCache::stats() {
    // TODO: Implement stats
    return nullptr;
}

} // namespace cache
} // namespace common
} // namespace google
} // namespace com
