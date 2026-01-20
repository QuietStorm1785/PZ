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
   FluentIterable$1(Iterable x0, Iterable var2) {
      super(x0);
      this.val$iterable = var2;
   }

   public Iterator<E> iterator() {
      return this.val$iterable.iterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
