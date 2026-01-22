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


class Iterables {
public:
   Iterables$4(Iterable var1, Predicate var2) {
      this.val$unfiltered = var1;
      this.val$retainIfTrue = var2;
   }

   public Iterator<T> iterator() {
      return Iterators.filter(this.val$unfiltered.iterator(), this.val$retainIfTrue);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
