#pragma once
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
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
 * Building full of toilet paper
 */
class RBOther : public RandomizedBuildingBase {
public:
  void randomizeBuilding(BuildingDef def) {
    def.bAlarmed = false;
    def.setHasBeenVisited(true);
    def.setAllExplored(true);
    IsoCell cell = IsoWorld.instance.CurrentCell;

    for (int int0 = def.x - 1; int0 < def.x2 + 1; int0++) {
      for (int int1 = def.y - 1; int1 < def.y2 + 1; int1++) {
        for (int int2 = 0; int2 < 8; int2++) {
          IsoGridSquare square = cell.getGridSquare(int0, int1, int2);
          if (square != nullptr) {
            for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
              IsoObject object = square.getObjects().get(int3);
              if (object.getContainer() != nullptr) {
                object.getContainer().emptyIt();
                object.getContainer().AddItems("Base.ToiletPaper",
                                               Rand.Next(10, 30));
                ItemPickerJava.updateOverlaySprite(object);
              }
            }
          }
        }
      }
    }
  }

  bool isValid(BuildingDef buildingDef, bool boolean0) {
    if (!super.isValid(buildingDef, boolean0)) {
      return false;
    } else {
      return buildingDef.getRooms().size() > 10
                 ? false
                 : !SpawnPoints.instance.isSpawnBuilding(buildingDef);
    }
  }

public
  RBOther() {
    this.name = "Other";
    this.setChance(1);
    this.setUnique(true);
  }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
