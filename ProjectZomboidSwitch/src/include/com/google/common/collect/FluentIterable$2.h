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


class FluentIterable {
public:
   FluentIterable$2(Iterable var1) {
      this.val$inputs = var1;
   }

   public Iterator<T> iterator() {
      return Iterators.concat(Iterables.transform(this.val$inputs, Iterables.toIterator()).iterator());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
