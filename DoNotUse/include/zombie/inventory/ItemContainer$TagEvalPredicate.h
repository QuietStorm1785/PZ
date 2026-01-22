#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/Lua/LuaManager.h"
#include <algorithm>

namespace zombie {
namespace inventory {


class ItemContainer {
public:
    std::string tag;
    LuaClosure functionObj;

   private ItemContainer$TagEvalPredicate() {
   }

   ItemContainer$TagEvalPredicate init(std::string var1, LuaClosure var2) {
      this.tag = var1;
      this.functionObj = Objects.requireNonNull(var2);
    return this;
   }

    bool test(InventoryItem var1) {
      return var1.hasTag(this.tag) && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1) == bool.TRUE;
   }
}
} // namespace inventory
} // namespace zombie
