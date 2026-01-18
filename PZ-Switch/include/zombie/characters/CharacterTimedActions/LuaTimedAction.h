#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace CharacterTimedActions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaTimedAction : public BaseAction {
public:
 KahluaTable table;
public
 static Object[] statObj = new Object[6];

public
 LuaTimedAction(KahluaTable _table, IsoGameCharacter chr) {
 super(chr);
 this->table = _table;
 void *object0 = _table.rawget("maxTime");
 this->MaxTime =
 LuaManager.converterManager.fromLuaToJava(object0, Integer.class);
 void *object1 = _table.rawget("stopOnWalk");
 void *object2 = _table.rawget("stopOnRun");
 void *object3 = _table.rawget("stopOnAim");
 void *object4 = _table.rawget("onUpdateFunc");
 if (object1 != nullptr) {
 this->StopOnWalk =
 LuaManager.converterManager.fromLuaToJava(object1, Boolean.class);
 }

 if (object2 != nullptr) {
 this->StopOnRun =
 LuaManager.converterManager.fromLuaToJava(object2, Boolean.class);
 }

 if (object3 != nullptr) {
 this->StopOnAim =
 LuaManager.converterManager.fromLuaToJava(object3, Boolean.class);
 }
 }

 void update() {
 statObj[0] = this->table.rawget("character");
 statObj[1] = this->table.rawget("param1");
 statObj[2] = this->table.rawget("param2");
 statObj[3] = this->table.rawget("param3");
 statObj[4] = this->table.rawget("param4");
 statObj[5] = this->table.rawget("param5");
 LuaManager.caller.pcallvoid(LuaManager.thread,
 this->table.rawget("onUpdateFunc"), statObj);
 super.update();
 }

 bool valid() {
 Object[] objects = LuaManager.caller.pcall(
 LuaManager.thread, this->table.rawget("isValidFunc"),
 this->table.rawget("character"), this->table.rawget("param1"),
 this->table.rawget("param2"), this->table.rawget("param3"),
 this->table.rawget("param4"), this->table.rawget("param5"));
 return objects.length > 0 && (Boolean)objects[0];
 }

 void start() {
 super.start();
 this->CurrentTime = 0.0F;
 LuaManager.caller.pcall(
 LuaManager.thread, this->table.rawget("startFunc"),
 this->table.rawget("character"), this->table.rawget("param1"),
 this->table.rawget("param2"), this->table.rawget("param3"),
 this->table.rawget("param4"), this->table.rawget("param5"));
 }

 void stop() {
 super.stop();
 LuaManager.caller.pcall(
 LuaManager.thread, this->table.rawget("onStopFunc"),
 this->table.rawget("character"), this->table.rawget("param1"),
 this->table.rawget("param2"), this->table.rawget("param3"),
 this->table.rawget("param4"), this->table.rawget("param5"));
 }

 void perform() {
 super.perform();
 LuaManager.caller.pcall(
 LuaManager.thread, this->table.rawget("performFunc"),
 this->table.rawget("character"), this->table.rawget("param1"),
 this->table.rawget("param2"), this->table.rawget("param3"),
 this->table.rawget("param4"), this->table.rawget("param5"));
 }
}
} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
