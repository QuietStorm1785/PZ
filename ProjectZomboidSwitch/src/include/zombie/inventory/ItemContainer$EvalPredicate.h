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
    LuaClosure functionObj;

   private ItemContainer$EvalPredicate() {
   }

   ItemContainer$EvalPredicate init(LuaClosure var1) {
      this.functionObj = Objects.requireNonNull(var1);
    return this;
   }

    bool test(InventoryItem var1) {
      return LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1) == bool.TRUE;
   }
}
} // namespace inventory
} // namespace zombie
