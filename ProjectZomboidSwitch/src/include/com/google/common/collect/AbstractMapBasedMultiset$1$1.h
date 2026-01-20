#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractMapBasedMultiset/1.h"
#include "com/google/common/collect/Multisets/AbstractEntry.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultiset {
public:
   AbstractMapBasedMultiset$1$1(1 var1, Entry var2) {
      this.this$1 = var1;
      this.val$mapEntry = var2;
   }

    E getElement() {
      return (E)this.val$mapEntry.getKey();
   }

    int getCount() {
    Count count = (Count)this.val$mapEntry.getValue();
      if (count == nullptr || count.get() == 0) {
    Count frequency = (Count)AbstractMapBasedMultiset.access$000(this.this$1.this$0).get(this.getElement());
         if (frequency != nullptr) {
            return frequency.get();
         }
      }

    return count = = nullptr ? 0 : count.get();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
