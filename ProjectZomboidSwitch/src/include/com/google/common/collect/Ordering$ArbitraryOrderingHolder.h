#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Ordering/ArbitraryOrdering.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class Ordering {
public:
   static const Ordering<Object> ARBITRARY_ORDERING = std::make_unique<ArbitraryOrdering>();

   private Ordering$ArbitraryOrderingHolder() {
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
