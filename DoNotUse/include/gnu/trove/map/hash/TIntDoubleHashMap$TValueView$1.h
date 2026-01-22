#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntDoubleHashMap/TValueView.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TIntDoubleHashMap {
public:
    bool first;

   TIntDoubleHashMap$TValueView$1(TValueView var1, std::stringstream var2) {
      this.this$1 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(double value) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(", ");
      }

      this.val$buf.append(value);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
