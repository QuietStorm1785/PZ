#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeBasedTable {
public:
   const Comparator<? super C> comparator;
    static const long serialVersionUID = 0L;

   TreeBasedTable$Factory(Comparator<? super C> comparator) {
      this.comparator = comparator;
   }

   public std::map<C, V> get() {
      return new std::map<>(this.comparator);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
