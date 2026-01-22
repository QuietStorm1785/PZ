#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Maps/EntrySet.h"
#include "com/google/common/collect/WellBehavedMap/EntrySet/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class WellBehavedMap {
public:
   private WellBehavedMap$EntrySet(WellBehavedMap var1) {
      this.this$0 = var1;
   }

   Map<K, V> map() {
      return this.this$0;
   }

   public Iterator<Entry<K, V>> iterator() {
      return std::make_shared<1>(this, this.this$0.keySet().iterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
