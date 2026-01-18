#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpawnPoints.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * This building will be 90% burnt (no fire started tho)
 */
class RBBurnt : public RandomizedBuildingBase {
public:
 void randomizeBuilding(BuildingDef def) {
 def.bAlarmed = false;
 def.setHasBeenVisited(true);
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int0 = def.x - 1; int0 < def.x2 + 1; int0++) {
 for (int int1 = def.y - 1; int1 < def.y2 + 1; int1++) {
 for (int int2 = 0; int2 < 8; int2++) {
 IsoGridSquare square = cell.getGridSquare(int0, int1, int2);
 if (square != nullptr && Rand.Next(100) < 90) {
 square.Burn(false);
 }
 }
 }
 }

 def.setAllExplored(true);
 def.bAlarmed = false;
 }

 /**
 * Description copied from class: RandomizedBuildingBase
 */
 bool isValid(BuildingDef def, bool force) {
 if (!super.isValid(def, force) {
 return false;
 } else {
 return def.getRooms().size() > 20
 ? false
 : !SpawnPoints.instance.isSpawnBuilding(def);
 }
 }

public
 RBBurnt() {
 this->name = "Burnt";
 this->setChance(3);
 }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
