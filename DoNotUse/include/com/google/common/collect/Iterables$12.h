#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterables {
public:
   Iterables$12(Iterable var1, Comparator var2) {
      this.val$iterables = var1;
      this.val$comparator = var2;
   }

   public Iterator<T> iterator() {
      return Iterators.mergeSorted(Iterables.transform(this.val$iterables, Iterables.toIterator()), this.val$comparator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
