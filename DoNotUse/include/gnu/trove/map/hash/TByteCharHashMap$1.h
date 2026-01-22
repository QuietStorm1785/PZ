#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TByteCharProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TByteCharHashMap {
public:
    bool first;

   TByteCharHashMap$1(TByteCharHashMap var1, std::stringstream var2) {
      this.this$0 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(uint8_t key, char value) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(", ");
      }

      this.val$buf.append((int)key);
      this.val$buf.append("=");
      this.val$buf.append(value);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
