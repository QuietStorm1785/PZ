#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/DenseImmutableTable/ImmutableArrayMap/1.h"
#include "com/google/common/collect/ImmutableMap/IteratorBasedImmutableMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class DenseImmutableTable {
public:
    const int size;

   DenseImmutableTable$ImmutableArrayMap(int size) {
      this.size = size;
   }

   abstract ImmutableMap<K, int> keyToIndex();

    bool isFull() {
      return this.size == this.keyToIndex().size();
   }

    K getKey(int index) {
      return (K)this.keyToIndex().keySet().asList().get(index);
   }

   abstract V getValue(int var1);

   ImmutableSet<K> createKeySet() {
      return this.isFull() ? this.keyToIndex().keySet() : super.createKeySet();
   }

    int size() {
      return this.size;
   }

    V get(@Nullable Object) {
    int keyIndex = (int)this.keyToIndex().get(key);
    return keyIndex = = nullptr ? nullptr : this.getValue(keyIndex);
   }

   UnmodifiableIterator<Entry<K, V>> entryIterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
