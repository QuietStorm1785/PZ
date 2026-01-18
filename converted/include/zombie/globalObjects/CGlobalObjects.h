#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/util/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CGlobalObjects {
public:
 protected static ArrayList<CGlobalObjectSystem> systems = std::make_unique<ArrayList<>>();
 protected static HashMap<String, KahluaTable> initialState = std::make_unique<HashMap<>>();

 static void noise(const std::string& message) {
 if (Core.bDebug) {
 DebugLog.log("CGlobalObjects: " + message);
 }
 }

 static CGlobalObjectSystem registerSystem(const std::string& name) {
 CGlobalObjectSystem cGlobalObjectSystem = getSystemByName(name);
 if (cGlobalObjectSystem.empty()) {
 cGlobalObjectSystem = newSystem(name);
 KahluaTable table0 = initialState.get(name);
 if (table0 != nullptr) {
 KahluaTableIterator kahluaTableIterator0 = table0.iterator();

 while (kahluaTableIterator0.advance()) {
 void* object0 = kahluaTableIterator0.getKey();
 void* object1 = kahluaTableIterator0.getValue();
 if ("_objects" == object0) {
 KahluaTable table1 = Type.tryCastTo(object1, KahluaTable.class);
 int int0 = 1;

 for (int int1 = table1.len(); int0 <= int1; int0++) {
 KahluaTable table2 = Type.tryCastTo(table1.rawget(int0), KahluaTable.class);
 int int2 = ((Double)table2.rawget("x")).intValue();
 int int3 = ((Double)table2.rawget("y")).intValue();
 int int4 = ((Double)table2.rawget("z")).intValue();
 table2.rawset("x", nullptr);
 table2.rawset("y", nullptr);
 table2.rawset("z", nullptr);
 CGlobalObject cGlobalObject = Type.tryCastTo(cGlobalObjectSystem.newObject(int2, int3, int4), CGlobalObject.class);
 KahluaTableIterator kahluaTableIterator1 = table2.iterator();

 while (kahluaTableIterator1.advance()) {
 cGlobalObject.getModData().rawset(kahluaTableIterator1.getKey(), kahluaTableIterator1.getValue());
 }
 }

 table1.wipe();
 } else {
 cGlobalObjectSystem.modData.rawset(object0, object1);
 }
 }
 }
 }

 return cGlobalObjectSystem;
 }

 static CGlobalObjectSystem newSystem(const std::string& name) {
 if (getSystemByName(name) != nullptr) {
 throw IllegalStateException("system with that name already exists");
 } else {
 noise("newSystem " + name);
 CGlobalObjectSystem cGlobalObjectSystem = new CGlobalObjectSystem(name);
 systems.add(cGlobalObjectSystem);
 return cGlobalObjectSystem;
 }
 }

 static int getSystemCount() {
 return systems.size();
 }

 static CGlobalObjectSystem getSystemByIndex(int index) {
 return index >= 0 && index < systems.size() ? systems.get(index) : nullptr;
 }

 static CGlobalObjectSystem getSystemByName(const std::string& name) {
 for (int int0 = 0; int0 < systems.size(); int0++) {
 CGlobalObjectSystem cGlobalObjectSystem = systems.get(int0);
 if (cGlobalObjectSystem.name == name) {
 return cGlobalObjectSystem;
 }
 }

 return nullptr;
 }

 static void initSystems() {
 LuaEventManager.triggerEvent("OnCGlobalObjectSystemInit");
 }

 static void loadInitialState(ByteBuffer bb) {
 uint8_t byte0 = bb.get();

 for (int int0 = 0; int0 < byte0; int0++) {
 std::string string = GameWindow.ReadStringUTF(bb);
 if (bb.get() != 0) {
 KahluaTable table = LuaManager.platform.newTable();
 initialState.put(string, table);
 TableNetworkUtils.load(table, bb);
 }
 }
 }

 static bool receiveServerCommand(const std::string& systemName, const std::string& command, KahluaTable args) {
 CGlobalObjectSystem cGlobalObjectSystem = getSystemByName(systemName);
 if (cGlobalObjectSystem.empty()) {
 throw IllegalStateException("system '" + systemName + "' not found");
 } else {
 cGlobalObjectSystem.receiveServerCommand(command, args);
 return true;
 }
 }

 static void Reset() {
 for (int int0 = 0; int0 < systems.size(); int0++) {
 CGlobalObjectSystem cGlobalObjectSystem = systems.get(int0);
 cGlobalObjectSystem.Reset();
 }

 systems.clear();
 initialState.clear();
 CGlobalObjectNetwork.Reset();
 }
}
} // namespace globalObjects
} // namespace zombie
