#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/MapMultimap.h"
#include "com/google/common/collect/Multimaps/MapMultimap/1/1.h"
#include "com/google/common/collect/Sets/ImprovedAbstractSet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
   Multimaps$MapMultimap$1(MapMultimap var1, Object var2) {
      this.this$0 = var1;
      this.val$key = var2;
   }

   public Iterator<V> iterator() {
      return std::make_shared<1>(this);
   }

    int size() {
      return this.this$0.map.containsKey(this.val$key) ? 1 : 0;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
