#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GlobalObject {
public:
 GlobalObjectSystem system;
 int x;
 int y;
 int z;
 const KahluaTable modData;

 GlobalObject(GlobalObjectSystem globalObjectSystem, int int0, int int1, int int2) {
 this->system = globalObjectSystem;
 this->x = int0;
 this->y = int1;
 this->z = int2;
 this->modData = LuaManager.platform.newTable();
 }

 GlobalObjectSystem getSystem() {
 return this->system;
 }

 void setLocation(int _x, int _y, int _z) {
 }

 int getX() {
 return this->x;
 }

 int getY() {
 return this->y;
 }

 int getZ() {
 return this->z;
 }

 KahluaTable getModData() {
 return this->modData;
 }

 void Reset() {
 this->system = nullptr;
 this->modData.wipe();
 }
}
} // namespace globalObjects
} // namespace zombie
