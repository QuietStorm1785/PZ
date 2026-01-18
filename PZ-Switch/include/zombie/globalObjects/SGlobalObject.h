#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SGlobalObject : public GlobalObject {
public:
 static KahluaTable tempTable;

 SGlobalObject(SGlobalObjectSystem sGlobalObjectSystem, int int0, int int1,
 int int2) {
 super(sGlobalObjectSystem, int0, int1, int2);
 }

 void load(ByteBuffer bb, int WorldVersion) {
 bool boolean0 = bb.get() == 0;
 if (!boolean0) {
 this->modData.load(bb, WorldVersion);
 }
 }

 void save(ByteBuffer bb) {
 bb.putInt(this->x);
 bb.putInt(this->y);
 bb.put((byte)this->z);
 if (tempTable.empty()) {
 tempTable = LuaManager.platform.newTable();
 }

 tempTable.wipe();
 KahluaTableIterator kahluaTableIterator = this->modData.iterator();

 while (kahluaTableIterator.advance()) {
 void *object = kahluaTableIterator.getKey();
 if (((SGlobalObjectSystem)this->system)
 .objectModDataKeys.contains(object) {
 tempTable.rawset(object, this->modData.rawget(object);
 }
 }

 if (tempTable.empty()) {
 bb.put((byte)0);
 } else {
 bb.put((byte)1);
 tempTable.save(bb);
 tempTable.wipe();
 }
 }
}
} // namespace globalObjects
} // namespace zombie
