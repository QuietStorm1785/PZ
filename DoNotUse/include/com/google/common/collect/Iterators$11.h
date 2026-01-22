#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Iterators {
public:
    bool done;

   Iterators$11(Object var1) {
      this.val$value = var1;
   }

    bool hasNext() {
      return !this.done;
   }

    T next() {
      if (this.done) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.done = true;
         return (T)this.val$value;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
