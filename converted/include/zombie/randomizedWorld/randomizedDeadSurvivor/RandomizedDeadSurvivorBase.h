#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RandomizedDeadSurvivorBase : public RandomizedBuildingBase {
public:
 void randomizeDeadSurvivor(BuildingDef def) {
 }

 bool isValid(BuildingDef buildingDef, bool var2) {
 return !SpawnPoints.instance.isSpawnBuilding(buildingDef);
 }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
