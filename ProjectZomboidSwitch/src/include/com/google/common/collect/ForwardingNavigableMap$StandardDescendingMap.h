#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/collect/ForwardingNavigableMap/StandardDescendingMap/1.h"
#include "com/google/common/collect/Maps/DescendingMap.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ForwardingNavigableMap {
public:
   public ForwardingNavigableMap$StandardDescendingMap(ForwardingNavigableMap var1) {
      this.this$0 = var1;
   }

   NavigableMap<K, V> forward() {
      return this.this$0;
   }

   protected Iterator<Entry<K, V>> entryIterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
