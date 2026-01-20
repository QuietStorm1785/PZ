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


class Iterators {
public:
    int count;

   Iterators$8(int var1, Iterator var2) {
      this.val$limitSize = var1;
      this.val$iterator = var2;
   }

    bool hasNext() {
      return this.count < this.val$limitSize && this.val$iterator.hasNext();
   }

    T next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.count++;
         return (T)this.val$iterator.next();
      }
   }

    void remove() {
      this.val$iterator.remove();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
