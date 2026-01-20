#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LongAddables {
public:
    LongAddable get() {
      return std::make_unique<LongAdder>();
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
