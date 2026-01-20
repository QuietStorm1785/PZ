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
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    const int hash;
   const ReferenceEntry<K, V> next;
   volatile ValueReference<K, V> valueReference = LocalCache.unset();

   LocalCache$WeakEntry(ReferenceQueue<K> queue, K key, int hash, @Nullable ReferenceEntry<K, V> next) {
      super(key, queue);
      this.hash = hash;
      this.next = next;
   }

    K getKey() {
      return this.get();
   }

    long getAccessTime() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setAccessTime(long time) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ReferenceEntry<K, V> getNextInAccessQueue() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setNextInAccessQueue(V> next) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ReferenceEntry<K, V> getPreviousInAccessQueue() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setPreviousInAccessQueue(V> previous) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    long getWriteTime() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setWriteTime(long time) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ReferenceEntry<K, V> getNextInWriteQueue() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setNextInWriteQueue(V> next) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ReferenceEntry<K, V> getPreviousInWriteQueue() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setPreviousInWriteQueue(V> previous) {
      throw std::make_unique<UnsupportedOperationException>();
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
