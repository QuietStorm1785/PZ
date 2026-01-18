#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/integration/LuaCaller.h"
#include "se/krka/kahlua/luaj/compiler/LuaCompiler.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"

namespace zombie {
namespace Lua {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Event {
public:
 static const int ADD = 0;
 static const int NUM_FUNCTIONS = 1;
 private Event.Add add;
 private Event.Remove remove;
 public ArrayList<LuaClosure> callbacks = std::make_unique<ArrayList<>>();
 std::string name;
 int index = 0;

 bool trigger(KahluaTable var1, LuaCaller luaCaller, Object[] objects) {
 if (this->callbacks.empty()) {
 return false;
 } else if (DebugOptions.instance.Checks.SlowLuaEvents.getValue()) {
 for (int int0 = 0; int0 < this->callbacks.size(); int0++) {
 try {
 LuaClosure luaClosure = this->callbacks.get(int0);
 long long0 = System.nanoTime();
 luaCaller.protectedCallVoid(LuaManager.thread, luaClosure, objects);
 double double0 = (System.nanoTime() - long0) / 1000000.0;
 if (double0 > 250.0) {
 DebugLog.Lua.warn("SLOW Lua event callback %s %s %dms", luaClosure.prototype.file, luaClosure, (int)double0);
 }
 } catch (Exception exception0) {
 ExceptionLogger.logException(exception0);
 }
 }

 return true;
 } else {
 for (int int1 = 0; int1 < this->callbacks.size(); int1++) {
 try {
 luaCaller.protectedCallVoid(LuaManager.thread, this->callbacks.get(int1), objects);
 } catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
 }
 }

 return true;
 }
 }

 public Event(const std::string& _name, int _index) {
 this->index = _index;
 this->name = _name;
 this->add = new Event.Add(this);
 this->remove = new Event.Remove(this);
 }

 void register(Platform platform, KahluaTable environment) {
 KahluaTable table = platform.newTable();
 table.rawset("Add", this->add);
 table.rawset("Remove", this->remove);
 environment.rawset(this->name, table);
 }

 public static class Add implements JavaFunction {
 Event e;

 public Add(Event _e) {
 this->e = _e;
 }

 /**
 * Description copied from interface: se.krka.kahlua.vm.JavaFunction
 * @return N, number of return values. The top N objects on the stack are considered the return values.
 */
 int call(LuaCallFrame callFrame, int nArguments) {
 if (LuaCompiler.rewriteEvents) {
 return 0;
 } else {
 void* object = callFrame.get(0);
 if (this->e.name.contains("CreateUI")) {
 bool boolean0 = false;
 }

 if (object instanceof LuaClosure luaClosure) {
 this->e.callbacks.add(luaClosure);
 }

 return 0;
 }
 }
 }

 public static class Remove implements JavaFunction {
 Event e;

 public Remove(Event _e) {
 this->e = _e;
 }

 /**
 * Description copied from interface: se.krka.kahlua.vm.JavaFunction
 * @return N, number of return values. The top N objects on the stack are considered the return values.
 */
 int call(LuaCallFrame callFrame, int nArguments) {
 if (LuaCompiler.rewriteEvents) {
 return 0;
 } else {
 if (callFrame.get(0) instanceof LuaClosure luaClosure) {
 this->e.callbacks.remove(luaClosure);
 }

 return 0;
 }
 }
 }
}
} // namespace Lua
} // namespace zombie
