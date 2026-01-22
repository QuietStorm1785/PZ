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


class RandomizedDeadSurvivorBase : public RandomizedBuildingBase {
public:
    void randomizeDeadSurvivor(BuildingDef var1) {
   }

    bool isValid(BuildingDef var1, bool var2) {
      return !SpawnPoints.instance.isSpawnBuilding(var1);
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
