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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LuaHookManager {
public:
 public static ArrayList<LuaClosure> OnTickCallbacks = std::make_unique<ArrayList<>>();
 static Object[] a = new Object[1];
 static Object[] b = new Object[2];
 static Object[] c = new Object[3];
 static Object[] d = new Object[4];
 static Object[] f = new Object[5];
 static Object[] g = new Object[6];
 private static ArrayList<Event> EventList = std::make_unique<ArrayList<>>();
 private static HashMap<String, Event> EventMap = std::make_unique<HashMap<>>();

 static bool TriggerHook(const std::string& string) {
 if (EventMap.containsKey(string) {
 Event event = EventMap.get(string);
 a[0] = nullptr;
 return event.trigger(LuaManager.env, LuaManager.caller, a);
 } else {
 return false;
 }
 }

 static bool TriggerHook(const std::string& string, void* object) {
 if (EventMap.containsKey(string) {
 Event event = EventMap.get(string);
 a[0] = object;
 return event.trigger(LuaManager.env, LuaManager.caller, a);
 } else {
 return false;
 }
 }

 static bool TriggerHook(const std::string& string, void* object0, void* object1) {
 if (EventMap.containsKey(string) {
 Event event = EventMap.get(string);
 b[0] = object0;
 b[1] = object1;
 return event.trigger(LuaManager.env, LuaManager.caller, b);
 } else {
 return false;
 }
 }

 static bool TriggerHook(const std::string& string, void* object0, void* object1, void* object2) {
 if (EventMap.containsKey(string) {
 Event event = EventMap.get(string);
 c[0] = object0;
 c[1] = object1;
 c[2] = object2;
 return event.trigger(LuaManager.env, LuaManager.caller, c);
 } else {
 return false;
 }
 }

 static bool TriggerHook(const std::string& string, void* object0, void* object1, void* object2, void* object3) {
 if (EventMap.containsKey(string) {
 Event event = EventMap.get(string);
 d[0] = object0;
 d[1] = object1;
 d[2] = object2;
 d[3] = object3;
 return event.trigger(LuaManager.env, LuaManager.caller, d);
 } else {
 return false;
 }
 }

 static bool TriggerHook(const std::string& string, void* object0, void* object1, void* object2, void* object3, void* object4) {
 if (EventMap.containsKey(string) {
 Event event = EventMap.get(string);
 f[0] = object0;
 f[1] = object1;
 f[2] = object2;
 f[3] = object3;
 f[4] = object4;
 return event.trigger(LuaManager.env, LuaManager.caller, f);
 } else {
 return false;
 }
 }

 static bool TriggerHook(const std::string& string, void* object0, void* object1, void* object2, void* object3, void* object4, void* object5) {
 if (EventMap.containsKey(string) {
 Event event = EventMap.get(string);
 g[0] = object0;
 g[1] = object1;
 g[2] = object2;
 g[3] = object3;
 g[4] = object4;
 g[5] = object5;
 return event.trigger(LuaManager.env, LuaManager.caller, g);
 } else {
 return false;
 }
 }

 static void AddEvent(const std::string& string) {
 if (!EventMap.containsKey(string) {
 Event event = new Event(string, EventList.size());
 EventList.add(event);
 EventMap.put(string, event);
 if (LuaManager.env.rawget("Hook") instanceof KahluaTable table) {
 event.register(LuaManager.platform, table);
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

 static void register(Platform platform, KahluaTable table1) {
 KahluaTable table0 = platform.newTable();
 table1.rawset("Hook", table0);
 AddEvents();
 }

 static void Reset() {
 for (auto& event : EventList) event.callbacks.clear();
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
