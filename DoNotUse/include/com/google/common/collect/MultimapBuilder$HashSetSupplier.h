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


class MultimapBuilder {
public:
    const int expectedValuesPerKey;

   MultimapBuilder$HashSetSupplier(int expectedValuesPerKey) {
      this.expectedValuesPerKey = CollectPreconditions.checkNonnegative(expectedValuesPerKey, "expectedValuesPerKey");
   }

   public Set<V> get() {
      return Sets.newHashSetWithExpectedSize(this.expectedValuesPerKey);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
