#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class HashBasedTable {
public:
    const int expectedSize;
    static const long serialVersionUID = 0L;

   HashBasedTable$Factory(int expectedSize) {
      this.expectedSize = expectedSize;
   }

   public Map<C, V> get() {
      return Maps.newLinkedHashMapWithExpectedSize(this.expectedSize);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
