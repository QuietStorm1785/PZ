#pragma once
#include <set>
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
   private const Comparator<? super V> comparator;

   MultimapBuilder$TreeSetSupplier(Comparator<? super V> comparator) {
      this.comparator = (Comparator<? super V>)Preconditions.checkNotNull(comparator);
   }

   public SortedSet<V> get() {
      return new std::set<>(this.comparator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
