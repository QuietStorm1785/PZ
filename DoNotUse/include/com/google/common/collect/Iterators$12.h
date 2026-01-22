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
   Iterators$12(Enumeration var1) {
      this.val$enumeration = var1;
   }

    bool hasNext() {
      return this.val$enumeration.hasMoreElements();
   }

    T next() {
      return (T)this.val$enumeration.nextElement();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
