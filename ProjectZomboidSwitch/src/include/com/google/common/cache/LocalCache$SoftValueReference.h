#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
   const ReferenceEntry<K, V> entry;

   LocalCache$SoftValueReference(ReferenceQueue<V> queue, V referent, ReferenceEntry<K, V> entry) {
      super(referent, queue);
      this.entry = entry;
   }

    int getWeight() {
    return 1;
   }

   public ReferenceEntry<K, V> getEntry() {
      return this.entry;
   }

    void notifyNewValue(V newValue) {
   }

   public ValueReference<K, V> copyFor(ReferenceQueue<V> queue, V value, ReferenceEntry<K, V> entry) {
      return new LocalCache$SoftValueReference<>(queue, value, entry);
   }

    bool isLoading() {
    return false;
   }

    bool isActive() {
    return true;
   }

    V waitForValue() {
      return this.get();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
