#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TCharObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {
namespace hash {


class TCharObjectHashMap {
public:
    bool first;

   TCharObjectHashMap$2(TCharObjectHashMap var1, std::stringstream var2) {
      this.this$0 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(char key, void* value) {
      if (this.first) {
         this.first = false;
      } else {
         this.val$buf.append(",");
      }

      this.val$buf.append(key);
      this.val$buf.append("=");
      this.val$buf.append(value);
    return true;
   }
}
} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
