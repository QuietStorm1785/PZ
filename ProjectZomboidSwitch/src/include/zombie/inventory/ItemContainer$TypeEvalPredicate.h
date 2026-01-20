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
    std::string type;
    LuaClosure functionObj;

   private ItemContainer$TypeEvalPredicate() {
   }

   ItemContainer$TypeEvalPredicate init(std::string var1, LuaClosure var2) {
      this.type = var1;
      this.functionObj = Objects.requireNonNull(var2);
    return this;
   }

    bool test(InventoryItem var1) {
      return ItemContainer.compareType(this.type, var1) && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1) == bool.TRUE;
   }
}
} // namespace inventory
} // namespace zombie
