#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/cache/LocalCache/SoftValueReference.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"
#include "com/google/common/cache/LocalCache/WeightedSoftValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {


enum class LocalCache {
   <K, V> ValueReference<K, V> referenceValue(Segment<K, V> segment, ReferenceEntry<K, V> entry, V value, int weight) {
      return (ValueReference<K, V>)(weight == 1
         ? std::make_shared<SoftValueReference>(segment.valueReferenceQueue, value, entry)
         : std::make_shared<WeightedSoftValueReference>(segment.valueReferenceQueue, value, entry, weight));
   }

   Equivalence<Object> defaultEquivalence() {
      return Equivalence.identity();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
