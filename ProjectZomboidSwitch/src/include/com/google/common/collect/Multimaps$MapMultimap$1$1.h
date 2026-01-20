#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Multimaps/MapMultimap/1.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multimaps {
public:
    int i;

   Multimaps$MapMultimap$1$1(1 var1) {
      this.this$1 = var1;
   }

    bool hasNext() {
      return this.i == 0 && this.this$1.this$0.map.containsKey(this.this$1.val$key);
   }

    V next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.i++;
         return (V)this.this$1.this$0.map.get(this.this$1.val$key);
      }
   }

    void remove() {
      CollectPreconditions.checkRemove(this.i == 1);
      this.i = -1;
      this.this$1.this$0.map.remove(this.this$1.val$key);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
