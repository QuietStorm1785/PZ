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
    void* arg;

   private ItemContainer$EvalArgPredicate() {
   }

   ItemContainer$EvalArgPredicate init(LuaClosure var1, Object var2) {
      this.functionObj = Objects.requireNonNull(var1);
      this.arg = var2;
    return this;
   }

    bool test(InventoryItem var1) {
      return LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1, this.arg) == bool.TRUE;
   }
}
} // namespace inventory
} // namespace zombie
