#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TByteObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TByteObjectHashMap {
public:
   TByteObjectHashMap$1(TByteObjectHashMap var1) {
      this.this$0 = var1;
   }

    bool execute(uint8_t key, V value) {
      this.this$0.put(key, value);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
