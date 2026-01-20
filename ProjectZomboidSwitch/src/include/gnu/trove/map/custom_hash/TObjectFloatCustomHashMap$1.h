#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TObjectFloatProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectFloatCustomHashMap {
public:
   TObjectFloatCustomHashMap$1(TObjectFloatCustomHashMap var1) {
      this.this$0 = var1;
   }

    bool execute(K key, float value) {
      this.this$0.put(key, value);
    return true;
   }
}
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
