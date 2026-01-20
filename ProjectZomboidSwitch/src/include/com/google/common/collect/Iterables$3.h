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
   Iterables$3(Iterable var1, int var2) {
      this.val$iterable = var1;
      this.val$size = var2;
   }

   public Iterator<List<T>> iterator() {
      return Iterators.paddedPartition(this.val$iterable.iterator(), this.val$size);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
