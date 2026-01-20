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
   Iterables$5(Iterable var1, Class var2) {
      this.val$unfiltered = var1;
      this.val$desiredType = var2;
   }

   public Iterator<T> iterator() {
      return Iterators.filter(this.val$unfiltered.iterator(), this.val$desiredType);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
