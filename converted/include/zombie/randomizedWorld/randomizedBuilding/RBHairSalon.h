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
class RBHairSalon : public RandomizedBuildingBase {
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
              if (Rand.NextBool(3) && object.getSurfaceOffsetNoTable() > 0.0F &&
                  square.getProperties().Val("waterAmount") == nullptr &&
                  !object.hasWater() &&
                  object.getProperties().Val("BedType") == nullptr) {
                int int4 = Rand.Next(12);
                switch (int4) {
                case 0:
                  this.addWorldItem("Comb", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 1:
                  this.addWorldItem("HairDyeBlonde", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 2:
                  this.addWorldItem("HairDyeBlack", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 3:
                  this.addWorldItem("HairDyeWhite", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                case 4:
                default:
                  break;
                case 5:
                  this.addWorldItem("HairDyePink", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 6:
                  this.addWorldItem("HairDyeYellow", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 7:
                  this.addWorldItem("HairDyeRed", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 8:
                  this.addWorldItem("HairDyeGinger", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 9:
                  this.addWorldItem("Hairgel", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 10:
                  this.addWorldItem("Hairspray", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                  break;
                case 11:
                  this.addWorldItem("Razor", square, 0.5F, 0.5F,
                                    object.getSurfaceOffsetNoTable() / 96.0F);
                }
              }
            }
          }
        }
      }
    }
  }

  bool roomValid(IsoGridSquare sq) {
        return sq.getRoom() != nullptr && "aesthetic" == sq.getRoom().getName());
  }

  /**
   * Description copied from class: RandomizedBuildingBase
   */
  bool isValid(BuildingDef def, bool force) {
    return def.getRoom("aesthetic") != nullptr || force;
  }

public
  RBHairSalon() {
    this.name = "Hair Salon";
    this.setAlwaysDo(true);
  }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
