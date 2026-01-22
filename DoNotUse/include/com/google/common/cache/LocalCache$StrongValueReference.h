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
    const V referent;

   LocalCache$StrongValueReference(V referent) {
      this.referent = referent;
   }

    V get() {
      return this.referent;
   }

    int getWeight() {
    return 1;
   }

   public ReferenceEntry<K, V> getEntry() {
    return nullptr;
   }

   public ValueReference<K, V> copyFor(ReferenceQueue<V> queue, V value, ReferenceEntry<K, V> entry) {
    return this;
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

    void notifyNewValue(V newValue) {
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
