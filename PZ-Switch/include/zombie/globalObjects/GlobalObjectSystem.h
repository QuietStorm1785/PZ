#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include <algorithm>
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

class GlobalObjectSystem {
public:
private
 static ArrayDeque<ArrayList<GlobalObject>> objectListPool =
 std::make_unique<ArrayDeque<>>();
 const std::string name;
 const KahluaTable modData;
protected
 ArrayList<GlobalObject> objects = std::make_unique<ArrayList<>>();
 const GlobalObjectLookup lookup = new GlobalObjectLookup(this);

 GlobalObjectSystem(String string) {
 this->name = string;
 this->modData = LuaManager.platform.newTable();
 }

 std::string getName() { return this->name; }

 KahluaTable getModData() { return this->modData; }

protected
 GlobalObject makeObject(int var1, int var2, int var3);

 GlobalObject newObject(int x, int y, int z) {
 if (this->getObjectAt(x, y, z) != nullptr) {
 throw IllegalStateException("already an object at " + x + "," + y +
 "," + z);
 } else {
 GlobalObject globalObject = this->makeObject(x, y, z);
 this->objects.add(globalObject);
 this->lookup.addObject(globalObject);
 return globalObject;
 }
 }

 void removeObject(GlobalObject object) {
 if (object.empty()) {
 throw NullPointerException("object is nullptr");
 } else if (object.system != this) {
 throw IllegalStateException("object not in this system");
 } else {
 this->objects.remove(object);
 this->lookup.removeObject(object);
 object.Reset();
 }
 }

 GlobalObject getObjectAt(int x, int y, int z) {
 return this->lookup.getObjectAt(x, y, z);
 }

 bool hasObjectsInChunk(int wx, int wy) {
 return this->lookup.hasObjectsInChunk(wx, wy);
 }

public
 ArrayList<GlobalObject> getObjectsInChunk(int wx, int wy) {
 return this->lookup.getObjectsInChunk(wx, wy, this->allocList());
 }

public
 ArrayList<GlobalObject> getObjectsAdjacentTo(int x, int y, int z) {
 return this->lookup.getObjectsAdjacentTo(x, y, z, this->allocList());
 }

 int getObjectCount() { return this->objects.size(); }

 GlobalObject getObjectByIndex(int index) {
 return index >= 0 && index < this->objects.size() ? this->objects.get(index)
 : nullptr;
 }

public
 ArrayList<GlobalObject> allocList() {
 return objectListPool.empty() ? std::make_unique<ArrayList<>>()
 : objectListPool.pop();
 }

 void finishedWithList(ArrayList<GlobalObject> list) {
 if (list != nullptr && !objectListPool.contains(list) {
 list.clear();
 objectListPool.add(list);
 }
 }

 void Reset() {
 for (int int0 = 0; int0 < this->objects.size(); int0++) {
 GlobalObject globalObject = this->objects.get(int0);
 globalObject.Reset();
 }

 this->objects.clear();
 this->modData.wipe();
 }
}
} // namespace globalObjects
} // namespace zombie
