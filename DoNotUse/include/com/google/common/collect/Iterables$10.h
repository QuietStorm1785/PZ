#pragma once
#include <queue>
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
   Iterables$10(Iterable var1) {
      this.val$iterable = var1;
   }

   public Iterator<T> iterator() {
      return std::make_shared<ConsumingQueueIterator>((std::queue)this.val$iterable);
   }

    std::string toString() {
      return "Iterables.consumingIterable(...)";
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
