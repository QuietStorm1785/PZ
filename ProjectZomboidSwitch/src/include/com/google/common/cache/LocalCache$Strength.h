#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Equivalence.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/Segment.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {


enum class LocalCache {
   STRONG,
   SOFT,
   WEAK;

   private LocalCache$Strength() {
   }

   abstract <K, V> ValueReference<K, V> referenceValue(Segment<K, V> var1, ReferenceEntry<K, V> var2, V var3, int var4);

   abstract Equivalence<Object> defaultEquivalence();
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
