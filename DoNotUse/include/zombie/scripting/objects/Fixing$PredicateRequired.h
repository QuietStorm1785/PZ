#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/InventoryItem.h"
#include "zombie/scripting/objects/Fixing/Fixer.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


class Fixing {
public:
    Fixer fixer;
    InventoryItem brokenItem;
    int uses;

   private Fixing$PredicateRequired() {
   }

    bool test(InventoryItem var1) {
      if (this.uses >= this.fixer.getNumberOfUse()) {
    return false;
      } else if (var1 == this.brokenItem) {
    return false;
      } else if (!this.fixer.getFixerName() == var1.getType())) {
    return false;
      } else {
    int var2 = Fixing.countUses(var1);
         if (var2 > 0) {
            this.uses += var2;
    return true;
         } else {
    return false;
         }
      }
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
