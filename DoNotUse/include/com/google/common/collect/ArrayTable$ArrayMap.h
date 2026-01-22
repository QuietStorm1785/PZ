#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ArrayTable/ArrayMap/1.h"
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ArrayTable {
public:
   private const ImmutableMap<K, int> keyIndex;

   private ArrayTable$ArrayMap(ImmutableMap<K, int> keyIndex) {
      this.keyIndex = keyIndex;
   }

   public Set<K> keySet() {
      return this.keyIndex.keySet();
   }

    K getKey(int index) {
      return (K)this.keyIndex.keySet().asList().get(index);
   }

   abstract std::string getKeyRole();

   abstract V getValue(int var1);

   abstract V setValue(int var1, V var2);

    int size() {
      return this.keyIndex.size();
   }

    bool isEmpty() {
      return this.keyIndex.empty();
   }

   Iterator<Entry<K, V>> entryIterator() {
      return std::make_shared<1>(this, this.size());
   }

    bool containsKey(@Nullable Object) {
      return this.keyIndex.containsKey(key);
   }

    V get(@Nullable Object) {
    int index = (int)this.keyIndex.get(key);
    return index = = nullptr ? nullptr : this.getValue(index);
   }

    V put(K key, V value) {
    int index = (int)this.keyIndex.get(key);
      if (index == nullptr) {
         throw IllegalArgumentException(this.getKeyRole() + " " + key + " not in " + this.keyIndex.keySet());
      } else {
         return this.setValue(index, value);
      }
   }

    V remove(void* key) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    void clear() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
