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
   Iterables$7(List var1, int var2) {
      this.val$list = var1;
      this.val$numberToSkip = var2;
   }

   public Iterator<T> iterator() {
    int toSkip = Math.min(this.val$list.size(), this.val$numberToSkip);
      return this.val$list.subList(toSkip, this.val$list.size()).iterator();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
