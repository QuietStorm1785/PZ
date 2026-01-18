#pragma once
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RandomizedDeadSurvivorBase : public RandomizedBuildingBase {
public:
 void randomizeDeadSurvivor(BuildingDef def) {}

 bool isValid(BuildingDef buildingDef, bool var2) {
 return !SpawnPoints.instance.isSpawnBuilding(buildingDef);
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
