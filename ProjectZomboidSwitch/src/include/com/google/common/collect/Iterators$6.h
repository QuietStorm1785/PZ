#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Predicate.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
   Iterators$6(Iterator var1, Predicate var2) {
      this.val$unfiltered = var1;
      this.val$retainIfTrue = var2;
   }

    T computeNext() {
      while (this.val$unfiltered.hasNext()) {
    T element = (T)this.val$unfiltered.next();
         if (this.val$retainIfTrue.apply(element)) {
    return element;
         }
      }

      return (T)this.endOfData();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
