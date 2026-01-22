#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


enum class MultimapBuilder {
   INSTANCE;

   public static <V> Supplier<List<V>> instance() {
      Supplier<List<V>> result = INSTANCE;
    return result;
   }

   public List<Object> get() {
      return std::make_unique<std::list<>>();
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
