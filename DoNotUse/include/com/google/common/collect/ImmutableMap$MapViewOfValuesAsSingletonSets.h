#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/IteratorBasedImmutableMap.h"
#include "com/google/common/collect/ImmutableMap/MapViewOfValuesAsSingletonSets/1.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   private ImmutableMap$MapViewOfValuesAsSingletonSets(ImmutableMap var1) {
      this.this$0 = var1;
   }

    int size() {
      return this.this$0.size();
   }

   public ImmutableSet<K> keySet() {
      return this.this$0.keySet();
   }

    bool containsKey(@Nullable Object) {
      return this.this$0.containsKey(key);
   }

   public ImmutableSet<V> get(@Nullable Object key) {
    V outerValue = (V)this.this$0.get(key);
    return outerValue = = nullptr ? nullptr : ImmutableSet.of(outerValue);
   }

    bool isPartialView() {
      return this.this$0.isPartialView();
   }

    int hashCode() {
      return this.this$0.hashCode();
   }

    bool isHashCodeFast() {
      return this.this$0.isHashCodeFast();
   }

   UnmodifiableIterator<Entry<K, ImmutableSet<V>>> entryIterator() {
      Iterator<Entry<K, V>> backingIterator = this.this$0.entrySet().iterator();
      return std::make_shared<1>(this, backingIterator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
