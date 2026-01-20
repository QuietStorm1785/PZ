#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Sets/SubSet.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Sets {
public:
   const ImmutableList<E> elements;
    int remainingSetBits;

   Sets$SubSet$1(SubSet var1) {
      this.this$0 = var1;
      this.elements = SubSet.access$100(this.this$0).keySet().asList();
      this.remainingSetBits = SubSet.access$200(this.this$0);
   }

    bool hasNext() {
      return this.remainingSetBits != 0;
   }

    E next() {
    int index = int.numberOfTrailingZeros(this.remainingSetBits);
      if (index == 32) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.remainingSetBits &= ~(1 << index);
         return (E)this.elements.get(index);
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
