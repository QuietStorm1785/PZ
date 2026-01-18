#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ai/astar/IPathfinder.h"
#include "zombie/ai/astar/Mover.h"
#include "zombie/ai/astar/Path.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace characters {
namespace CharacterTimedActions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LuaTimedActionNew : public BaseAction {
public:
 KahluaTable table;

 public LuaTimedActionNew(KahluaTable _table, IsoGameCharacter chr) {
 super(chr);
 this->table = _table;
 void* object0 = _table.rawget("maxTime");
 this->MaxTime = LuaManager.converterManager.fromLuaToJava(object0, Integer.class);
 void* object1 = _table.rawget("stopOnWalk");
 void* object2 = _table.rawget("stopOnRun");
 void* object3 = _table.rawget("stopOnAim");
 void* object4 = _table.rawget("caloriesModifier");
 void* object5 = _table.rawget("useProgressBar");
 void* object6 = _table.rawget("forceProgressBar");
 void* object7 = _table.rawget("loopedAction");
 if (object1 != nullptr) {
 this->StopOnWalk = LuaManager.converterManager.fromLuaToJava(object1, Boolean.class);
 }

 if (object2 != nullptr) {
 this->StopOnRun = LuaManager.converterManager.fromLuaToJava(object2, Boolean.class);
 }

 if (object3 != nullptr) {
 this->StopOnAim = LuaManager.converterManager.fromLuaToJava(object3, Boolean.class);
 }

 if (object4 != nullptr) {
 this->caloriesModifier = LuaManager.converterManager.fromLuaToJava(object4, Float.class);
 }

 if (object5 != nullptr) {
 this->UseProgressBar = LuaManager.converterManager.fromLuaToJava(object5, Boolean.class);
 }

 if (object6 != nullptr) {
 this->ForceProgressBar = LuaManager.converterManager.fromLuaToJava(object6, Boolean.class);
 }

 if (object7 != nullptr) {
 this->loopAction = LuaManager.converterManager.fromLuaToJava(object7, Boolean.class);
 }
 }

 void waitToStart() {
 bool boolean0 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, this->table.rawget("waitToStart"), this->table);
 if (boolean0 == Boolean.FALSE) {
 super.waitToStart();
 }
 }

 void update() {
 super.update();
 LuaManager.caller.pcallvoid(LuaManager.thread, this->table.rawget("update"), this->table);
 }

 bool valid() {
 Object[] objects = LuaManager.caller.pcall(LuaManager.thread, this->table.rawget("isValid"), this->table);
 return objects.length > 1 && objects[1] instanceof Boolean && (Boolean)objects[1];
 }

 void start() {
 super.start();
 this->CurrentTime = 0.0F;
 LuaManager.caller.pcall(LuaManager.thread, this->table.rawget("start"), this->table);
 }

 void stop() {
 super.stop();
 LuaManager.caller.pcall(LuaManager.thread, this->table.rawget("stop"), this->table);
 }

 void perform() {
 super.perform();
 LuaManager.caller.pcall(LuaManager.thread, this->table.rawget("perform"), this->table);
 }

 void Failed(Mover mover) {
 this->table.rawset("path", nullptr);
 LuaManager.caller.pcallvoid(LuaManager.thread, this->table.rawget("failedPathfind"), this->table);
 }

 void Succeeded(Path path, Mover mover) {
 this->table.rawset("path", path);
 LuaManager.caller.pcallvoid(LuaManager.thread, this->table.rawget("succeededPathfind"), this->table);
 }

 void Pathfind(IsoGameCharacter chr, int x, int y, int z) {
 }

 std::string getName() {
 return "timedActionPathfind";
 }

 void setCurrentTime(float time) {
 this->CurrentTime = PZMath.clamp(time, 0.0F, (float)this->MaxTime);
 }

 void setTime(int maxTime) {
 this->MaxTime = maxTime;
 }

 void OnAnimEvent(AnimEvent event) {
 void* object = this->table.rawget("animEvent");
 if (object != nullptr) {
 LuaManager.caller.pcallvoid(LuaManager.thread, object, this->table, event.m_EventName, event.m_ParameterValue);
 }
 }

 std::string getMetaType() {
 return this->table != nullptr && this->table.getMetatable() != nullptr ? this->table.getMetatable().getString("Type") : "";
 }
}
} // namespace CharacterTimedActions
} // namespace characters
} // namespace zombie
