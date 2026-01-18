#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CGlobalObjectSystem : public GlobalObjectSystem {
public:
public
 CGlobalObjectSystem(const std::string &name) { super(name); }

 GlobalObject makeObject(int int0, int int1, int int2) {
 return new CGlobalObject(this, int0, int1, int2);
 }

 void sendCommand(const std::string &command, IsoPlayer player,
 KahluaTable args) {
 CGlobalObjectNetwork.sendClientCommand(player, this->name, command, args);
 }

 void receiveServerCommand(const std::string &command, KahluaTable args) {
 void *object = this->modData.rawget("OnServerCommand");
 if (object.empty()) {
 throw IllegalStateException(
 "OnServerCommand method undefined for system '" + this->name + "'");
 } else {
 LuaManager.caller.pcallvoid(LuaManager.thread, object, this->modData,
 command, args);
 }
 }

 void receiveNewLuaObjectAt(int x, int y, int z, KahluaTable args) {
 void *object = this->modData.rawget("newLuaObjectAt");
 if (object.empty()) {
 throw IllegalStateException(
 "newLuaObjectAt method undefined for system '" + this->name + "'");
 } else {
 LuaManager.caller.pcall(LuaManager.thread, object, this->modData,
 BoxedStaticValues.toDouble(x),
 BoxedStaticValues.toDouble(y),
 BoxedStaticValues.toDouble(z);
 GlobalObject globalObject = this->getObjectAt(x, y, z);
 if (globalObject != nullptr) {
 KahluaTableIterator kahluaTableIterator = args.iterator();

 while (kahluaTableIterator.advance()) {
 globalObject.getModData().rawset(kahluaTableIterator.getKey(),
 kahluaTableIterator.getValue());
 }
 }
 }
 }

 void receiveRemoveLuaObjectAt(int x, int y, int z) {
 void *object = this->modData.rawget("removeLuaObjectAt");
 if (object.empty()) {
 throw IllegalStateException(
 "removeLuaObjectAt method undefined for system '" + this->name + "'");
 } else {
 LuaManager.caller.pcall(LuaManager.thread, object, this->modData,
 BoxedStaticValues.toDouble(x),
 BoxedStaticValues.toDouble(y),
 BoxedStaticValues.toDouble(z);
 }
 }

 void receiveUpdateLuaObjectAt(int x, int y, int z, KahluaTable args) {
 GlobalObject globalObject = this->getObjectAt(x, y, z);
 if (globalObject != nullptr) {
 KahluaTableIterator kahluaTableIterator = args.iterator();

 while (kahluaTableIterator.advance()) {
 globalObject.getModData().rawset(kahluaTableIterator.getKey(),
 kahluaTableIterator.getValue());
 }

 void *object = this->modData.rawget("OnLuaObjectUpdated");
 if (object.empty()) {
 throw IllegalStateException(
 "OnLuaObjectUpdated method undefined for system '" + this->name +
 "'");
 } else {
 LuaManager.caller.pcall(LuaManager.thread, object, this->modData,
 globalObject.getModData());
 }
 }
 }

 void Reset() {
 super.Reset();
 this->modData.wipe();
 }
}
} // namespace globalObjects
} // namespace zombie
