#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZEmptyIterable {
public:
   PZEmptyIterable$1(PZEmptyIterable var1) {
      this.this$0 = var1;
   }

    bool hasNext() {
    return false;
   }

    T next() {
      throw ArrayIndexOutOfBoundsException("Empty Iterator. Has no data.");
   }
}
} // namespace list
} // namespace util
} // namespace zombie
