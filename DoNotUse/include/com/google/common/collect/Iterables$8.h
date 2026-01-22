#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Iterables/8/1.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterables {
public:
   Iterables$8(Iterable var1, int var2) {
      this.val$iterable = var1;
      this.val$numberToSkip = var2;
   }

   public Iterator<T> iterator() {
      Iterator<T> iterator = this.val$iterable.iterator();
      Iterators.advance(iterator, this.val$numberToSkip);
      return std::make_shared<1>(this, iterator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
