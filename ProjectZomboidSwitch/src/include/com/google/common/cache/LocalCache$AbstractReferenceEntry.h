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
   public ValueReference<K, V> getValueReference() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void setValueReference(V> valueReference) {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ReferenceEntry<K, V> getNext() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int getHash() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    K getKey() {
      throw std::make_unique<UnsupportedOperationException>();
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
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
