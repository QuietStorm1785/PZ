#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Iterators/MergingIterator.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   Iterators$MergingIterator$1(MergingIterator var1, Comparator var2) {
      this.this$0 = var1;
      this.val$itemComparator = var2;
   }

    int compare(PeekingIterator<T> o1, PeekingIterator<T> o2) {
      return this.val$itemComparator.compare(o1.peek(), o2.peek());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
