#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/ImmutableRangeSet/AsSet.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableRangeSet {
public:
   const Iterator<Range<C>> rangeItr;
   Iterator<C> elemItr;

   ImmutableRangeSet$AsSet$2(AsSet var1) {
      this.this$1 = var1;
      this.rangeItr = ImmutableRangeSet.access$000(this.this$1.this$0).reverse().iterator();
      this.elemItr = Iterators.emptyIterator();
   }

    C computeNext() {
      while (!this.elemItr.hasNext()) {
         if (!this.rangeItr.hasNext()) {
            return (C)((Comparable)this.endOfData());
         }

         this.elemItr = ContiguousSet.create((Range)this.rangeItr.next(), AsSet.access$100(this.this$1)).descendingIterator();
      }

      return (C)((Comparable)this.elemItr.next());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
