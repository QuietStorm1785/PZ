#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/LuaCaller.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/Lua/Event/Add.h"
#include "zombie/Lua/Event/Remove.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"

namespace zombie {
namespace Lua {


class Event {
public:
    static const int ADD = 0;
    static const int NUM_FUNCTIONS = 1;
    const Add add;
    const Remove remove;
   public const std::vector<LuaClosure> callbacks = std::make_unique<std::vector<>>();
    std::string name;
    int index = 0;

    bool trigger(KahluaTable var1, LuaCaller var2, Object[] var3) {
      if (this.callbacks.empty()) {
    return false;
      } else if (DebugOptions.instance.Checks.SlowLuaEvents.getValue()) {
         for (int var12 = 0; var12 < this.callbacks.size(); var12++) {
            try {
    LuaClosure var5 = this.callbacks.get(var12);
    long var6 = System.nanoTime();
               var2.protectedCallVoid(LuaManager.thread, var5, var3);
    double var8 = (System.nanoTime() - var6) / 1000000.0;
               if (var8 > 250.0) {
                  DebugLog.Lua.warn("SLOW Lua event callback %s %s %dms", new Object[]{var5.prototype.file, var5, (int)var8});
               }
            } catch (Exception var10) {
               ExceptionLogger.logException(var10);
            }
         }

    return true;
      } else {
         for (int var4 = 0; var4 < this.callbacks.size(); var4++) {
            try {
               var2.protectedCallVoid(LuaManager.thread, this.callbacks.get(var4), var3);
            } catch (Exception var11) {
               ExceptionLogger.logException(var11);
            }
         }

    return true;
      }
   }

    public Event(const std::string& var1, int var2) {
      this.index = var2;
      this.name = var1;
      this.add = std::make_shared<Add>(this);
      this.remove = std::make_shared<Remove>(this);
   }

    void register(Platform var1, KahluaTable var2) {
    KahluaTable var3 = var1.newTable();
      var3.rawset("Add", this.add);
      var3.rawset("Remove", this.remove);
      var2.rawset(this.name, var3);
   }
}
} // namespace Lua
} // namespace zombie
