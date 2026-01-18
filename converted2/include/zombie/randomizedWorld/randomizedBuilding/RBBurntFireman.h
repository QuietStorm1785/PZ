#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpawnPoints.h"
#include "zombie/vehicles/BaseVehicle.h"
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
 * This building will be 70% burnt (no fire started tho)  Also spawn 1 to 3
 * fireman zombies inside it (65% of them to be male)
 */
class RBBurntFireman : public RandomizedBuildingBase {
public:
  void randomizeBuilding(BuildingDef def) {
    def.bAlarmed = false;
    int int0 = Rand.Next(1, 4);
    def.setHasBeenVisited(true);
    IsoCell cell = IsoWorld.instance.CurrentCell;

    for (int int1 = def.x - 1; int1 < def.x2 + 1; int1++) {
      for (int int2 = def.y - 1; int2 < def.y2 + 1; int2++) {
        for (int int3 = 0; int3 < 8; int3++) {
          IsoGridSquare square = cell.getGridSquare(int1, int2, int3);
          if (square != nullptr && Rand.Next(100) < 70) {
            square.Burn(false);
          }
        }
      }
    }

    def.setAllExplored(true);
    std::vector arrayList = this.addZombies(def, int0, "FiremanFullSuit", 35,
                                            this.getLivingRoomOrKitchen(def));

    for (int int4 = 0; int4 < arrayList.size(); int4++) {
      ((IsoZombie)arrayList.get(int4)).getInventory().setExplored(true);
    }

    BaseVehicle vehicle;
    if (Rand.NextBool(2)) {
      vehicle = this.spawnCarOnNearestNav("Base.PickUpVanLightsFire", def);
    } else {
      vehicle = this.spawnCarOnNearestNav("Base.PickUpTruckLightsFire", def);
    }

    if (vehicle != nullptr) {
      vehicle.setAlarmed(false);
    }

    if (vehicle != nullptr && !arrayList.isEmpty()) {
      ((IsoZombie)arrayList.get(Rand.Next(arrayList.size())))
          .addItemToSpawnAtDeath(vehicle.createVehicleKey());
    }
  }

  bool isValid(BuildingDef buildingDef, bool boolean0) {
    if (!super.isValid(buildingDef, boolean0)) {
      return false;
    } else {
      return buildingDef.getRooms().size() > 20
                 ? false
                 : !SpawnPoints.instance.isSpawnBuilding(buildingDef);
    }
  }

public
  RBBurntFireman() {
    this.name = "Burnt Fireman";
    this.setChance(2);
  }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
