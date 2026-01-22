#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/EntrySet.h"
#include "com/google/common/collect/Maps/IteratorBasedAbstractMap.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Maps {
public:
   Maps$IteratorBasedAbstractMap$1(IteratorBasedAbstractMap var1) {
      this.this$0 = var1;
   }

   Map<K, V> map() {
      return this.this$0;
   }

   public Iterator<Entry<K, V>> iterator() {
      return this.this$0.entryIterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
