#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace Lua {


class LuaHookManager {
public:
   public static const std::vector<LuaClosure> OnTickCallbacks = std::make_unique<std::vector<>>();
   static Object[] a = new Object[1];
   static Object[] b = new Object[2];
   static Object[] c = new Object[3];
   static Object[] d = new Object[4];
   static Object[] f = new Object[5];
   static Object[] g = new Object[6];
   private static const std::vector<Event> EventList = std::make_unique<std::vector<>>();
   private static const std::unordered_map<std::string, Event> EventMap = std::make_unique<std::unordered_map<>>();

    static bool TriggerHook(const std::string& var0) {
      if (EventMap.containsKey(var0)) {
    Event var1 = EventMap.get(var0);
         a[0] = nullptr;
         return var1.trigger(LuaManager.env, LuaManager.caller, a);
      } else {
    return false;
      }
   }

    static bool TriggerHook(const std::string& var0, void* var1) {
      if (EventMap.containsKey(var0)) {
    Event var2 = EventMap.get(var0);
         a[0] = var1;
         return var2.trigger(LuaManager.env, LuaManager.caller, a);
      } else {
    return false;
      }
   }

    static bool TriggerHook(const std::string& var0, void* var1, void* var2) {
      if (EventMap.containsKey(var0)) {
    Event var3 = EventMap.get(var0);
         b[0] = var1;
         b[1] = var2;
         return var3.trigger(LuaManager.env, LuaManager.caller, b);
      } else {
    return false;
      }
   }

    static bool TriggerHook(const std::string& var0, void* var1, void* var2, void* var3) {
      if (EventMap.containsKey(var0)) {
    Event var4 = EventMap.get(var0);
         c[0] = var1;
         c[1] = var2;
         c[2] = var3;
         return var4.trigger(LuaManager.env, LuaManager.caller, c);
      } else {
    return false;
      }
   }

    static bool TriggerHook(const std::string& var0, void* var1, void* var2, void* var3, void* var4) {
      if (EventMap.containsKey(var0)) {
    Event var5 = EventMap.get(var0);
         d[0] = var1;
         d[1] = var2;
         d[2] = var3;
         d[3] = var4;
         return var5.trigger(LuaManager.env, LuaManager.caller, d);
      } else {
    return false;
      }
   }

    static bool TriggerHook(const std::string& var0, void* var1, void* var2, void* var3, void* var4, void* var5) {
      if (EventMap.containsKey(var0)) {
    Event var6 = EventMap.get(var0);
         f[0] = var1;
         f[1] = var2;
         f[2] = var3;
         f[3] = var4;
         f[4] = var5;
         return var6.trigger(LuaManager.env, LuaManager.caller, f);
      } else {
    return false;
      }
   }

    static bool TriggerHook(const std::string& var0, void* var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      if (EventMap.containsKey(var0)) {
    Event var7 = EventMap.get(var0);
         g[0] = var1;
         g[1] = var2;
         g[2] = var3;
         g[3] = var4;
         g[4] = var5;
         g[5] = var6;
         return var7.trigger(LuaManager.env, LuaManager.caller, g);
      } else {
    return false;
      }
   }

    static void AddEvent(const std::string& var0) {
      if (!EventMap.containsKey(var0)) {
    Event var1 = std::make_shared<Event>(var0, EventList.size());
         EventList.push_back(var1);
         EventMap.put(var0, var1);
         if (LuaManager.env.rawget("Hook") instanceof KahluaTable var3) {
            var1.register(LuaManager.platform, var3);
         } else {
            DebugLog.log("ERROR: 'Hook' table not found or not a table");
         }
      }
   }

    static void AddEvents() {
      AddEvent("AutoDrink");
      AddEvent("UseItem");
      AddEvent("Attack");
      AddEvent("CalculateStats");
      AddEvent("WeaponHitCharacter");
      AddEvent("WeaponSwing");
      AddEvent("WeaponSwingHitPoint");
   }

    static void clear() {
      a[0] = nullptr;
      b[0] = nullptr;
      b[1] = nullptr;
      c[0] = nullptr;
      c[1] = nullptr;
      c[2] = nullptr;
      d[0] = nullptr;
      d[1] = nullptr;
      d[2] = nullptr;
      d[3] = nullptr;
      f[0] = nullptr;
      f[1] = nullptr;
      f[2] = nullptr;
      f[3] = nullptr;
      f[4] = nullptr;
      g[0] = nullptr;
      g[1] = nullptr;
      g[2] = nullptr;
      g[3] = nullptr;
      g[4] = nullptr;
      g[5] = nullptr;
   }

    static void register(Platform var0, KahluaTable var1) {
    KahluaTable var2 = var0.newTable();
      var1.rawset("Hook", var2);
      AddEvents();
   }

    static void Reset() {
    for (auto& var1 : EventList)         var1.callbacks.clear();
      }

      EventList.clear();
      EventMap.clear();
   }

    int call(LuaCallFrame var1, int var2) {
    return 0;
   }

    int OnTick(LuaCallFrame var1, int var2) {
    return 0;
   }
}
} // namespace Lua
} // namespace zombie
