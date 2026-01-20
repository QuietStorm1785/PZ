#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/SoftValueReference.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    const int weight;

   LocalCache$WeightedSoftValueReference(ReferenceQueue<V> queue, V referent, ReferenceEntry<K, V> entry, int weight) {
      super(queue, referent, entry);
      this.weight = weight;
   }

    int getWeight() {
      return this.weight;
   }

   public ValueReference<K, V> copyFor(ReferenceQueue<V> queue, V value, ReferenceEntry<K, V> entry) {
      return new LocalCache$WeightedSoftValueReference<K, V>(queue, value, entry, this.weight);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
