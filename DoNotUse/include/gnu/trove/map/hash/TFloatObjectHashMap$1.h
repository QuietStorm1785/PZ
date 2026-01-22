#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TFloatObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TFloatObjectHashMap {
public:
   TFloatObjectHashMap$1(TFloatObjectHashMap var1) {
      this.this$0 = var1;
   }

    bool execute(float key, V value) {
      this.this$0.put(key, value);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
