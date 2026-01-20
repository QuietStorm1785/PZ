#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/cache/LocalCache/WeakAccessWriteEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


enum class LocalCache {
   <K, V> ReferenceEntry<K, V> newEntry(Segment<K, V> segment, K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      return std::make_shared<WeakAccessWriteEntry>(segment.keyReferenceQueue, key, hash, next);
   }

   <K, V> ReferenceEntry<K, V> copyEntry(Segment<K, V> segment, ReferenceEntry<K, V> original, ReferenceEntry<K, V> newNext) {
      ReferenceEntry<K, V> newEntry = super.copyEntry(segment, original, newNext);
      this.copyAccessEntry(original, newEntry);
      this.copyWriteEntry(original, newEntry);
    return newEntry;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
