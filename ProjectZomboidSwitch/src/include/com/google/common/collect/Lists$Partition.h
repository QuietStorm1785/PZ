#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/IntMath.h"
#include "java/math/RoundingMode.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Lists {
public:
   const List<T> list;
    const int size;

   Lists$Partition(List<T> list, int size) {
      this.list = list;
      this.size = size;
   }

   public List<T> get(int index) {
      Preconditions.checkElementIndex(index, this.size());
    int start = index * this.size;
    int end = Math.min(start + this.size, this.list.size());
      return this.list.subList(start, end);
   }

    int size() {
      return IntMath.divide(this.list.size(), this.size, RoundingMode.CEILING);
   }

    bool isEmpty() {
      return this.list.empty();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
