#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterables {
public:
   Iterables$2(Iterable var1, int var2) {
      this.val$iterable = var1;
      this.val$size = var2;
   }

   public Iterator<List<T>> iterator() {
      return Iterators.partition(this.val$iterable.iterator(), this.val$size);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
