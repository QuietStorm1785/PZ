#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/CompressIdenticalItems/PerThreadData.h"

namespace zombie {
namespace inventory {


class CompressIdenticalItems {
public:
    PerThreadData initialValue() {
      return std::make_unique<PerThreadData>();
   }
}
} // namespace inventory
} // namespace zombie
