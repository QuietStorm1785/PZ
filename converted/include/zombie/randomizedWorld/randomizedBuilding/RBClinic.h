#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
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
 * Add some food on table
 */
class RBClinic : public RandomizedBuildingBase {
public:
  void randomizeBuilding(BuildingDef def) {
    IsoCell cell = IsoWorld.instance.CurrentCell;

    for (int int0 = def.x - 1; int0 < def.x2 + 1; int0++) {
      for (int int1 = def.y - 1; int1 < def.y2 + 1; int1++) {
        for (int int2 = 0; int2 < 8; int2++) {
          IsoGridSquare square = cell.getGridSquare(int0, int1, int2);
          if (square != nullptr && this.roomValid(square)) {
            for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
              IsoObject object = square.getObjects().get(int3);
              if (Rand.NextBool(2) && object.getSurfaceOffsetNoTable() > 0.0F &&
                  object.getContainer() == nullptr &&
                  square.getProperties().Val("waterAmount") == nullptr &&
                  !object.hasWater()) {
                int int4 = Rand.Next(1, 3);

                for (int int5 = 0; int5 < int4; int5++) {
                  int int6 = Rand.Next(12);
                  switch (int6) {
                  case 0:
                    this.addWorldItem("Scalpel", square, Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 1:
                    this.addWorldItem("Bandage", square, Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 2:
                    this.addWorldItem("Pills", square, Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 3:
                    this.addWorldItem("AlcoholWipes", square,
                                      Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 4:
                    this.addWorldItem("Bandaid", square, Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 5:
                    this.addWorldItem("CottonBalls", square,
                                      Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 6:
                    this.addWorldItem("Disinfectant", square,
                                      Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 7:
                    this.addWorldItem("SutureNeedle", square,
                                      Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 8:
                    this.addWorldItem("SutureNeedleHolder", square,
                                      Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 9:
                    this.addWorldItem("Tweezers", square, Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 10:
                    this.addWorldItem("Gloves_Surgical", square,
                                      Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 11:
                    this.addWorldItem("Hat_SurgicalMask_Blue", square,
                                      Rand.Next(0.4F, 0.6F),
                                      Rand.Next(0.4F, 0.6F),
                                      object.getSurfaceOffsetNoTable() / 96.0F);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  bool roomValid(IsoGridSquare sq) {
        return sq.getRoom() != nullptr
            && ("hospitalroom" == sq.getRoom().getName()) || "clinic" == sq.getRoom().getName()) || "medical" == sq.getRoom().getName()));
  }

  /**
   * Description copied from class: RandomizedBuildingBase
   */
  bool isValid(BuildingDef def, bool force) {
    return def.getRoom("medical") != nullptr ||
           def.getRoom("clinic") != nullptr || force;
  }

public
  RBClinic() {
    this.name = "Clinic (Vet, Doctor..)";
    this.setAlwaysDo(true);
  }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
