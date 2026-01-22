#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/custom_hash/TObjectIntCustomHashMap/TIntValueCollection.h"
#include "gnu/trove/procedure/TIntProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace custom_hash {


class TObjectIntCustomHashMap {
public:
    bool first;

   TObjectIntCustomHashMap$TIntValueCollection$1(TIntValueCollection var1, std::stringstream var2) {
      this.this$1 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(int value) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(", ");
      }

      this.val$buf.append(value);
    return true;
   }
}
} // namespace custom_hash
} // namespace map
} // namespace trove
} // namespace gnu
