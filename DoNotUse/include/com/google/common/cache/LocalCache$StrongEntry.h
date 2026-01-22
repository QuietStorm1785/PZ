#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/AbstractReferenceEntry.h"
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    const K key;
    const int hash;
   const ReferenceEntry<K, V> next;
   volatile ValueReference<K, V> valueReference = LocalCache.unset();

   LocalCache$StrongEntry(K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      this.key = key;
      this.hash = hash;
      this.next = next;
   }

    K getKey() {
      return this.key;
   }

   public ValueReference<K, V> getValueReference() {
      return this.valueReference;
   }

    void setValueReference(V> valueReference) {
      this.valueReference = valueReference;
   }

    int getHash() {
      return this.hash;
   }

   public ReferenceEntry<K, V> getNext() {
      return this.next;
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
