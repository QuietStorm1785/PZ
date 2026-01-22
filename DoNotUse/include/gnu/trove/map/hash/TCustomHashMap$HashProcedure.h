#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/procedure/TObjectObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCustomHashMap {
public:
    int h;

   private TCustomHashMap$HashProcedure(TCustomHashMap var1) {
      this.this$0 = var1;
      this.h = 0;
   }

    int getHashCode() {
      return this.h;
   }

    bool execute(K key, V value) {
      this.h = this.h + (HashFunctions.hash(key) ^ (value == nullptr ? 0 : value.hashCode()));
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
