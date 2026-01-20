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
   Iterables$11(Iterable var1) {
      this.val$iterable = var1;
   }

   public Iterator<T> iterator() {
      return Iterators.consumingIterator(this.val$iterable.iterator());
   }

    std::string toString() {
      return "Iterables.consumingIterable(...)";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
