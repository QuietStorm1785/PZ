#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/DescendingMap.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractNavigableMap {
public:
   private AbstractNavigableMap$DescendingMap(AbstractNavigableMap var1) {
      this.this$0 = var1;
   }

   NavigableMap<K, V> forward() {
      return this.this$0;
   }

   Iterator<Entry<K, V>> entryIterator() {
      return this.this$0.descendingEntryIterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
