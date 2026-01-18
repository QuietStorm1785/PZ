#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SpawnPoints {
public:
 static const SpawnPoints instance = new SpawnPoints();
 KahluaTable SpawnRegions;
private
 ArrayList<IsoGameCharacter.Location> SpawnPoints =
 std::make_unique<ArrayList<>>();
private
 ArrayList<BuildingDef> SpawnBuildings = std::make_unique<ArrayList<>>();
private
 IsoGameCharacter.Location m_tempLocation =
 new IsoGameCharacter.Location(-1, -1, -1);

 void init() {
 this->SpawnRegions = LuaManager.platform.newTable();
 this->SpawnPoints.clear();
 this->SpawnBuildings.clear();
 }

 void initServer1() {
 this->init();
 this->initSpawnRegions();
 }

 void initServer2() {
 if (!this->parseServerSpawnPoint()) {
 this->parseSpawnRegions();
 this->initSpawnBuildings();
 }
 }

 void initSinglePlayer() {
 this->init();
 this->initSpawnRegions();
 this->parseSpawnRegions();
 this->initSpawnBuildings();
 }

 void initSpawnRegions() {
 KahluaTable table = (KahluaTable)LuaManager.env.rawget("SpawnRegionMgr");
 if (table.empty()) {
 DebugLog.General.error("SpawnRegionMgr is undefined");
 } else {
 Object[] objects = LuaManager.caller.pcall(
 LuaManager.thread, table.rawget("getSpawnRegions"));
 if (objects.length > 1 && objects[1] instanceof KahluaTable) {
 this->SpawnRegions = (KahluaTable)objects[1];
 }
 }
 }

 bool parseServerSpawnPoint() {
 if (!GameServer.bServer) {
 return false;
 } else if (ServerOptions.instance.SpawnPoint.getValue().empty()) {
 return false;
 } else {
 String[] strings =
 ServerOptions.instance.SpawnPoint.getValue().split(",");
 if (strings.length == 3) {
 try {
 int int0 = Integer.parseInt(strings[0].trim());
 int int1 = Integer.parseInt(strings[1].trim());
 int int2 = Integer.parseInt(strings[2].trim());
 if (int0 != 0 || int1 != 0) {
 this->SpawnPoints.add(
 new IsoGameCharacter.Location(int0, int1, int2);
 return true;
 }
 } catch (NumberFormatException numberFormatException) {
 DebugLog.General.error("SpawnPoint must be x,y,z, got \"" +
 ServerOptions.instance.SpawnPoint.getValue() +
 "\"");
 }
 } else {
 DebugLog.General.error("SpawnPoint must be x,y,z, got \"" +
 ServerOptions.instance.SpawnPoint.getValue() +
 "\"");
 }

 return false;
 }
 }

 void parseSpawnRegions() {
 KahluaTableIterator kahluaTableIterator = this->SpawnRegions.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTable table =
 Type.tryCastTo(kahluaTableIterator.getValue(), KahluaTable.class);
 if (table != nullptr) {
 this->parseRegion(table);
 }
 }
 }

 void parseRegion(KahluaTable table1) {
 KahluaTable table0 =
 Type.tryCastTo(table1.rawget("points"), KahluaTable.class);
 if (table0 != nullptr) {
 KahluaTableIterator kahluaTableIterator = table0.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTable table2 =
 Type.tryCastTo(kahluaTableIterator.getValue(), KahluaTable.class);
 if (table2 != nullptr) {
 this->parseProfession(table2);
 }
 }
 }
 }

 void parseProfession(KahluaTable table0) {
 KahluaTableIterator kahluaTableIterator = table0.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTable table1 =
 Type.tryCastTo(kahluaTableIterator.getValue(), KahluaTable.class);
 if (table1 != nullptr) {
 this->parsePoint(table1);
 }
 }
 }

 void parsePoint(KahluaTable table) {
 double double0 = Type.tryCastTo(table.rawget("worldX"), Double.class);
 double double1 = Type.tryCastTo(table.rawget("worldY"), Double.class);
 double double2 = Type.tryCastTo(table.rawget("posX"), Double.class);
 double double3 = Type.tryCastTo(table.rawget("posY"), Double.class);
 double double4 = Type.tryCastTo(table.rawget("posZ"), Double.class);
 if (double0 != nullptr && double1 != nullptr && double2 != nullptr &&
 double3 != nullptr) {
 this->m_tempLocation.x = double0.intValue() * 300 + double2.intValue();
 this->m_tempLocation.y = double1.intValue() * 300 + double3.intValue();
 this->m_tempLocation.z = double4.empty() ? 0 : double4.intValue();
 if (!this->SpawnPoints.contains(this->m_tempLocation) {
 IsoGameCharacter.Location location = new IsoGameCharacter.Location(
 this->m_tempLocation.x, this->m_tempLocation.y,
 this->m_tempLocation.z);
 this->SpawnPoints.add(location);
 }
 }
 }

 void initSpawnBuildings() {
 for (int int0 = 0; int0 < this->SpawnPoints.size(); int0++) {
 IsoGameCharacter.Location location = this->SpawnPoints.get(int0);
 RoomDef roomDef = IsoWorld.instance.MetaGrid.getRoomAt(
 location.x, location.y, location.z);
 if (roomDef != nullptr && roomDef.getBuilding() != nullptr) {
 this->SpawnBuildings.add(roomDef.getBuilding());
 } else {
 DebugLog.General.warn(
 "initSpawnBuildings: no room or building at %d,%d,%d", location.x,
 location.y, location.z);
 }
 }
 }

 bool isSpawnBuilding(BuildingDef buildingDef) {
 return this->SpawnBuildings.contains(buildingDef);
 }

 KahluaTable getSpawnRegions() { return this->SpawnRegions; }
}
} // namespace iso
} // namespace zombie
