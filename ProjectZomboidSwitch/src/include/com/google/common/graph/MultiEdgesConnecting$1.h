#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/AbstractIterator.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace graph {


class MultiEdgesConnecting {
public:
   MultiEdgesConnecting$1(MultiEdgesConnecting var1, Iterator var2) {
      this.this$0 = var1;
      this.val$entries = var2;
   }

    E computeNext() {
      while (this.val$entries.hasNext()) {
         Entry<E, ?> entry = (Entry<E, ?>)this.val$entries.next();
         if (MultiEdgesConnecting.access$000(this.this$0) == entry.getValue())) {
            return (E)entry.getKey();
         }
      }

      return (E)this.endOfData();
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
