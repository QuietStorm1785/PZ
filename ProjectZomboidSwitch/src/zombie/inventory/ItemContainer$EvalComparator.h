#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/LuaReturn.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/Lua/LuaManager.h"
#include <algorithm>

namespace zombie {
namespace inventory {


class ItemContainer {
public:
    LuaClosure functionObj;

   private ItemContainer$EvalComparator() {
   }

   ItemContainer$EvalComparator init(LuaClosure var1) {
      this.functionObj = Objects.requireNonNull(var1);
    return this;
   }

    int compare(InventoryItem var1, InventoryItem var2) {
    LuaReturn var3 = LuaManager.caller.protectedCall(LuaManager.thread, this.functionObj, new Object[]{var1, var2});
      if (var3.isSuccess() && !var3.empty() && var3.getFirst() instanceof double) {
    double var4 = (double)var3.getFirst();
         return double.compare(var4, 0.0);
      } else {
    return 0;
      }
   }
}
} // namespace inventory
} // namespace zombie
