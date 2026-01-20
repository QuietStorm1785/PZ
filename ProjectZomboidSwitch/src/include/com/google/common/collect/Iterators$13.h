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


class Iterators {
public:
   Iterators$13(Iterator var1) {
      this.val$iterator = var1;
   }

    bool hasMoreElements() {
      return this.val$iterator.hasNext();
   }

    T nextElement() {
      return (T)this.val$iterator.next();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
