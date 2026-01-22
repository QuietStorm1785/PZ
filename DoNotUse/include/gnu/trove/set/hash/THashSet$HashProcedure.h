#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/impl/HashFunctions.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace set {
namespace hash {


class THashSet {
public:
    int h;

   private THashSet$HashProcedure(THashSet var1) {
      this.this$0 = var1;
      this.h = 0;
   }

    int getHashCode() {
      return this.h;
   }

    bool execute(E key) {
      this.h = this.h + HashFunctions.hash(key);
    return true;
   }
}
} // namespace hash
} // namespace set
} // namespace trove
} // namespace gnu
