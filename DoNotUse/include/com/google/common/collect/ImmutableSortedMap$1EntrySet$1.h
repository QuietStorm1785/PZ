#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableSortedMap/1EntrySet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableSortedMap {
public:
   ImmutableSortedMap$1EntrySet$1(1EntrySet var1) {
      this.this$1 = var1;
   }

   public Entry<K, V> get(int index) {
      return Maps.immutableEntry(
         ImmutableSortedMap.access$200(this.this$1.this$0).asList().get(index), ImmutableSortedMap.access$300(this.this$1.this$0).get(index)
      );
   }

   ImmutableCollection<Entry<K, V>> delegateCollection() {
      return this.this$1;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
