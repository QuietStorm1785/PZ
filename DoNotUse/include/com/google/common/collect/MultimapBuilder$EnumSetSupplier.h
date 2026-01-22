#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class MultimapBuilder {
public:
   private const Class<V> clazz;

   MultimapBuilder$EnumSetSupplier(Class<V> clazz) {
      this.clazz = (Class<V>)Preconditions.checkNotNull(clazz);
   }

   public Set<V> get() {
      return EnumSet.noneOf(this.clazz);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
