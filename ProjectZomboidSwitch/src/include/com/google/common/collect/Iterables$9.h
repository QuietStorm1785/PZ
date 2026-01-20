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
   Iterables$9(Iterable var1, int var2) {
      this.val$iterable = var1;
      this.val$limitSize = var2;
   }

   public Iterator<T> iterator() {
      return Iterators.limit(this.val$iterable.iterator(), this.val$limitSize);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
