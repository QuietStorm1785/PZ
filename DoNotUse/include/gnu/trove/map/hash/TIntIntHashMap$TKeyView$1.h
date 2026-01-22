#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntIntHashMap/TKeyView.h"
#include "gnu/trove/procedure/TIntProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TIntIntHashMap {
public:
    bool first;

   TIntIntHashMap$TKeyView$1(TKeyView var1, std::stringstream var2) {
      this.this$1 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(int key) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(", ");
      }

      this.val$buf.append(key);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
