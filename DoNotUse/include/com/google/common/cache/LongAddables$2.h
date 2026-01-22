#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Supplier.h"
#include "com/google/common/cache/LongAddables/PureJavaLongAddable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LongAddables {
public:
    LongAddable get() {
      return std::make_shared<PureJavaLongAddable>(nullptr);
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
