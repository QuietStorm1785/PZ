#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableMap/MapViewOfValuesAsSingletonSets.h"
#include "com/google/common/collect/ImmutableMap/MapViewOfValuesAsSingletonSets/1/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableMap {
public:
   ImmutableMap$MapViewOfValuesAsSingletonSets$1(MapViewOfValuesAsSingletonSets var1, Iterator var2) {
      this.this$1 = var1;
      this.val$backingIterator = var2;
   }

    bool hasNext() {
      return this.val$backingIterator.hasNext();
   }

   public Entry<K, ImmutableSet<V>> next() {
      Entry<K, V> backingEntry = (Entry<K, V>)this.val$backingIterator.next();
      return std::make_shared<1>(this, backingEntry);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
