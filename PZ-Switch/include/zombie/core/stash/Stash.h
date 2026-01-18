#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/core/Translator.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/ScriptManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace stash {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Stash {
public:
 std::string name;
 std::string type;
 std::string item;
 std::string customName;
 int buildingX;
 int buildingY;
 std::string spawnTable;
public
 ArrayList<StashAnnotation> annotations;
 bool spawnOnlyOnZed;
 int minDayToSpawn = -1;
 int maxDayToSpawn = -1;
 int minTrapToSpawn = -1;
 int maxTrapToSpawn = -1;
 int zombies;
public
 ArrayList<StashContainer> containers;
 int barricades;

public
 Stash(const std::string &_name) { this->name = _name; }

 void load(KahluaTableImpl stashDesc) {
 this->type = stashDesc.rawgetStr("type");
 this->item = stashDesc.rawgetStr("item");
 StashBuilding stashBuilding =
 new StashBuilding(this->name, stashDesc.rawgetInt("buildingX"),
 stashDesc.rawgetInt("buildingY"));
 StashSystem.possibleStashes.add(stashBuilding);
 this->buildingX = stashBuilding.buildingX;
 this->buildingY = stashBuilding.buildingY;
 this->spawnTable = stashDesc.rawgetStr("spawnTable");
 this->customName = Translator.getText(stashDesc.rawgetStr("customName"));
 this->zombies = stashDesc.rawgetInt("zombies");
 this->barricades = stashDesc.rawgetInt("barricades");
 this->spawnOnlyOnZed = stashDesc.rawgetBool("spawnOnlyOnZed");
 std::string string0 = stashDesc.rawgetStr("daysToSpawn");
 if (string0 != nullptr) {
 String[] strings0 = string0.split("-");
 if (strings0.length == 2) {
 this->minDayToSpawn = Integer.parseInt(strings0[0]);
 this->maxDayToSpawn = Integer.parseInt(strings0[1]);
 } else {
 this->minDayToSpawn = Integer.parseInt(strings0[0]);
 }
 }

 std::string string1 = stashDesc.rawgetStr("traps");
 if (string1 != nullptr) {
 String[] strings1 = string1.split("-");
 if (strings1.length == 2) {
 this->minTrapToSpawn = Integer.parseInt(strings1[0]);
 this->maxTrapToSpawn = Integer.parseInt(strings1[1]);
 } else {
 this->minTrapToSpawn = Integer.parseInt(strings1[0]);
 this->maxTrapToSpawn = this->minTrapToSpawn;
 }
 }

 KahluaTable table0 = (KahluaTable)stashDesc.rawget("containers");
 if (table0 != nullptr) {
 this->containers = std::make_unique<ArrayList<>>();
 KahluaTableIterator kahluaTableIterator0 = table0.iterator();

 while (kahluaTableIterator0.advance()) {
 KahluaTableImpl kahluaTableImpl0 =
 (KahluaTableImpl)kahluaTableIterator0.getValue();
 StashContainer stashContainer =
 new StashContainer(kahluaTableImpl0.rawgetStr("room"),
 kahluaTableImpl0.rawgetStr("containerSprite"),
 kahluaTableImpl0.rawgetStr("containerType"));
 stashContainer.contX = kahluaTableImpl0.rawgetInt("contX");
 stashContainer.contY = kahluaTableImpl0.rawgetInt("contY");
 stashContainer.contZ = kahluaTableImpl0.rawgetInt("contZ");
 stashContainer.containerItem =
 kahluaTableImpl0.rawgetStr("containerItem");
 if (stashContainer.containerItem != nullptr &&
 ScriptManager.instance.getItem(stashContainer.containerItem) ==
 nullptr) {
 DebugLog.General.error("Stash containerItem \"%s\" doesn't exist.",
 stashContainer.containerItem);
 }

 this->containers.add(stashContainer);
 }
 }

 if ("Map" == this->type) {
 KahluaTableImpl kahluaTableImpl1 =
 (KahluaTableImpl)stashDesc.rawget("annotations");
 if (kahluaTableImpl1 != nullptr) {
 this->annotations = std::make_unique<ArrayList<>>();
 KahluaTableIterator kahluaTableIterator1 =
 kahluaTableImpl1.iterator();

 while (kahluaTableIterator1.advance()) {
 KahluaTable table1 = (KahluaTable)kahluaTableIterator1.getValue();
 StashAnnotation stashAnnotation = new StashAnnotation();
 stashAnnotation.fromLua(table1);
 this->annotations.add(stashAnnotation);
 }
 }
 }
 }

 std::string getName() { return this->name; }

 std::string getItem() { return this->item; }

 int getBuildingX() { return this->buildingX; }

 int getBuildingY() { return this->buildingY; }
}
} // namespace stash
} // namespace core
} // namespace zombie
