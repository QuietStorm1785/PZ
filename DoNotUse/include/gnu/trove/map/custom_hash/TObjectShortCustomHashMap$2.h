#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TObjectShortProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectShortCustomHashMap {
public:
    bool first;

   TObjectShortCustomHashMap$2(TObjectShortCustomHashMap var1, std::stringstream var2) {
      this.this$0 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(K key, short value) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(",");
      }

      this.val$buf.append(key).append("=").append((int)value);
    return true;
   }
}
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
