#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class TCustomHashSet {
public:
    bool first;

   TCustomHashSet$1(TCustomHashSet var1, std::stringstream var2) {
      this.this$0 = var1;
      this.val$buf = var2;
      this.first = true;
   }

    bool execute(void* value) {
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
} // namespace set
} // namespace trove
} // namespace gnu
