#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SliceY.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/TableNetworkUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SGlobalObjects {
public:
 protected static ArrayList<SGlobalObjectSystem> systems = std::make_unique<ArrayList<>>();

 static void noise(const std::string& message) {
 if (Core.bDebug) {
 DebugLog.log("SGlobalObjects: " + message);
 }
 }

 static SGlobalObjectSystem registerSystem(const std::string& name) {
 SGlobalObjectSystem sGlobalObjectSystem = getSystemByName(name);
 if (sGlobalObjectSystem == nullptr) {
 sGlobalObjectSystem = newSystem(name);
 sGlobalObjectSystem.load();
 }

 return sGlobalObjectSystem;
 }

 static SGlobalObjectSystem newSystem(const std::string& name) {
 if (getSystemByName(name) != nullptr) {
 throw IllegalStateException("system with that name already exists");
 } else {
 noise("newSystem " + name);
 SGlobalObjectSystem sGlobalObjectSystem = new SGlobalObjectSystem(name);
 systems.add(sGlobalObjectSystem);
 return sGlobalObjectSystem;
 }
 }

 static int getSystemCount() {
 return systems.size();
 }

 static SGlobalObjectSystem getSystemByIndex(int index) {
 return index >= 0 && index < systems.size() ? systems.get(index) : nullptr;
 }

 static SGlobalObjectSystem getSystemByName(const std::string& name) {
 for (int int0 = 0; int0 < systems.size(); int0++) {
 SGlobalObjectSystem sGlobalObjectSystem = systems.get(int0);
 if (sGlobalObjectSystem.name == name) {
 return sGlobalObjectSystem;
 }
 }

 return nullptr;
 }

 static void update() {
 for (int int0 = 0; int0 < systems.size(); int0++) {
 SGlobalObjectSystem sGlobalObjectSystem = systems.get(int0);
 sGlobalObjectSystem.update();
 }
 }

 static void chunkLoaded(int wx, int wy) {
 for (int int0 = 0; int0 < systems.size(); int0++) {
 SGlobalObjectSystem sGlobalObjectSystem = systems.get(int0);
 sGlobalObjectSystem.chunkLoaded(wx, wy);
 }
 }

 static void initSystems() {
 if (!GameClient.bClient) {
 LuaEventManager.triggerEvent("OnSGlobalObjectSystemInit");
 if (!GameServer.bServer) {
 try {
 synchronized (SliceY.SliceBufferLock) {
 SliceY.SliceBuffer.clear();
 saveInitialStateForClient(SliceY.SliceBuffer);
 SliceY.SliceBuffer.flip();
 CGlobalObjects.loadInitialState(SliceY.SliceBuffer);
 }
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }
 }
 }

 static void saveInitialStateForClient(ByteBuffer bb) {
 bb.put((byte)systems.size());

 for (int int0 = 0; int0 < systems.size(); int0++) {
 SGlobalObjectSystem sGlobalObjectSystem = systems.get(int0);
 GameWindow.WriteStringUTF(bb, sGlobalObjectSystem.name);
 KahluaTable table0 = sGlobalObjectSystem.getInitialStateForClient();
 if (table0 == nullptr) {
 table0 = LuaManager.platform.newTable();
 }

 KahluaTable table1 = LuaManager.platform.newTable();
 table0.rawset("_objects", table1);

 for (int int1 = 0; int1 < sGlobalObjectSystem.getObjectCount(); int1++) {
 GlobalObject globalObject = sGlobalObjectSystem.getObjectByIndex(int1);
 KahluaTable table2 = LuaManager.platform.newTable();
 table2.rawset("x", BoxedStaticValues.toDouble(globalObject.getX()));
 table2.rawset("y", BoxedStaticValues.toDouble(globalObject.getY()));
 table2.rawset("z", BoxedStaticValues.toDouble(globalObject.getZ()));

 for (String string : sGlobalObjectSystem.objectSyncKeys) {
 table2.rawset(string, globalObject.getModData().rawget(string);
 }

 table1.rawset(int1 + 1, table2);
 }

 if (table0 != nullptr && !table0.empty()) {
 bb.put((byte)1);
 TableNetworkUtils.save(table0, bb);
 } else {
 bb.put((byte)0);
 }
 }
 }

 static bool receiveClientCommand(const std::string& systemName, const std::string& command, IsoPlayer playerObj, KahluaTable args) {
 noise("receiveClientCommand " + systemName + " " + command + " OnlineID=" + playerObj.getOnlineID());
 SGlobalObjectSystem sGlobalObjectSystem = getSystemByName(systemName);
 if (sGlobalObjectSystem == nullptr) {
 throw IllegalStateException("system '" + systemName + "' not found");
 } else {
 sGlobalObjectSystem.receiveClientCommand(command, playerObj, args);
 return true;
 }
 }

 static void load() {
 }

 static void save() {
 for (int int0 = 0; int0 < systems.size(); int0++) {
 SGlobalObjectSystem sGlobalObjectSystem = systems.get(int0);
 sGlobalObjectSystem.save();
 }
 }

 static void OnIsoObjectChangedItself(const std::string& systemName, IsoObject isoObject) {
 if (!GameClient.bClient) {
 SGlobalObjectSystem sGlobalObjectSystem = getSystemByName(systemName);
 if (sGlobalObjectSystem != nullptr) {
 sGlobalObjectSystem.OnIsoObjectChangedItself(isoObject);
 }
 }
 }

 static void Reset() {
 for (int int0 = 0; int0 < systems.size(); int0++) {
 SGlobalObjectSystem sGlobalObjectSystem = systems.get(int0);
 sGlobalObjectSystem.Reset();
 }

 systems.clear();
 GlobalObjectLookup.Reset();
 }
}
} // namespace globalObjects
} // namespace zombie
