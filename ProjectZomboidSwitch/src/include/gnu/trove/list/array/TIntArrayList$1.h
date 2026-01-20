#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace list {
namespace array {

class TIntArrayList {
public:
   TIntArrayList$1(int[] x0, int x1, boolean x2) {
      super(x0, x1, x2);
   }

    void ensureCapacity(int capacity) {
      if (capacity > this._data.length) {
         throw IllegalStateException("Can not grow std::vector wrapped external array");
      }
   }
}
} // namespace array
} // namespace list
} // namespace trove
} // namespace gnu
