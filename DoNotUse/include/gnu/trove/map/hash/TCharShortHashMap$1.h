#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TCharShortProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharShortHashMap {
public:
    bool first;

   TCharShortHashMap$1(TCharShortHashMap var1, std::stringstream var2) {
      this.this$0 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(char key, short value) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(", ");
      }

      this.val$buf.append(key);
      this.val$buf.append("=");
      this.val$buf.append((int)value);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
