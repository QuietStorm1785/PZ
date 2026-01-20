#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeBasedTable {
public:
    C lastValue;

   TreeBasedTable$2(TreeBasedTable var1, Iterator var2, Comparator var3) {
      this.this$0 = var1;
      this.val$merged = var2;
      this.val$comparator = var3;
   }

    C computeNext() {
      while (this.val$merged.hasNext()) {
    C next = (C)this.val$merged.next();
    bool duplicate = this.lastValue != nullptr && this.val$comparator.compare(next, this.lastValue) == 0;
         if (!duplicate) {
            this.lastValue = next;
            return this.lastValue;
         }
      }

      this.lastValue = nullptr;
      return (C)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
