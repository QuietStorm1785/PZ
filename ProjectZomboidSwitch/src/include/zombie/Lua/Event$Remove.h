#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"

namespace zombie {
namespace Lua {


class Event {
public:
    Event e;

   public Event$Remove(Event var1) {
      this.e = var1;
   }

    int call(LuaCallFrame var1, int var2) {
      if (LuaCompiler.rewriteEvents) {
    return 0;
      } else {
         if (var1.get(0) instanceof LuaClosure var4) {
            this.e.callbacks.remove(var4);
         }

    return 0;
      }
   }
}
} // namespace Lua
} // namespace zombie
