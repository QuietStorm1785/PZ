#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets/4.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   Sets$4$1(4 var1, Iterator var2, Iterator var3) {
      this.this$0 = var1;
      this.val$itr1 = var2;
      this.val$itr2 = var3;
   }

    E computeNext() {
      while (this.val$itr1.hasNext()) {
    E elem1 = (E)this.val$itr1.next();
         if (!this.this$0.val$set2.contains(elem1)) {
    return elem1;
         }
      }

      while (this.val$itr2.hasNext()) {
    E elem2 = (E)this.val$itr2.next();
         if (!this.this$0.val$set1.contains(elem2)) {
    return elem2;
         }
      }

      return (E)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
