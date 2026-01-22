#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TByteShortHashMap/TKeyView.h"
#include "gnu/trove/procedure/TByteProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TByteShortHashMap {
public:
    bool first;

   TByteShortHashMap$TKeyView$1(TKeyView var1, std::stringstream var2) {
      this.this$1 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(uint8_t key) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(", ");
      }

      this.val$buf.append((int)key);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
