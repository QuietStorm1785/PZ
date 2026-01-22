#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/cache/LocalCache/StrongEntry.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


enum class LocalCache {
   <K, V> ReferenceEntry<K, V> newEntry(Segment<K, V> segment, K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      return std::make_shared<StrongEntry>(key, hash, next);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
