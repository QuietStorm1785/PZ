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
 * Random clutter in office
 */
class RBOffice : public RandomizedBuildingBase {
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
              if (object.isTableSurface() && Rand.NextBool(2) &&
                  square.getObjects().size() == 2 &&
                  object.getProperties().Val("BedType") == nullptr &&
                  object.isTableSurface() &&
                  (object.getContainer() == nullptr ||
                   "desk" == object.getContainer().getType()))) {
                  int int4 = Rand.Next(0, 8);
                  switch (int4) {
                  case 0:
                    square.AddWorldInventoryItem(
                        "Pen", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 1:
                    square.AddWorldInventoryItem(
                        "Pencil", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 2:
                    square.AddWorldInventoryItem(
                        "Crayons", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 3:
                    square.AddWorldInventoryItem(
                        "RedPen", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 4:
                    square.AddWorldInventoryItem(
                        "BluePen", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 5:
                    square.AddWorldInventoryItem(
                        "Eraser", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                  }

                  int int5 = Rand.Next(0, 6);
                  switch (int5) {
                  case 0:
                    square.AddWorldInventoryItem(
                        "Doodle", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 1:
                    square.AddWorldInventoryItem(
                        "Book", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 2:
                    square.AddWorldInventoryItem(
                        "Notebook", Rand.Next(0.4F, 0.8F),
                        Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 3:
                    square.AddWorldInventoryItem(
                        "SheetPaper2", Rand.Next(0.4F, 0.8F),
                        Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                  }

                  int int6 = Rand.Next(0, 7);
                  switch (int6) {
                  case 0:
                    square.AddWorldInventoryItem(
                        "MugRed", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 1:
                    square.AddWorldInventoryItem(
                        "Mugl", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 2:
                    square.AddWorldInventoryItem(
                        "MugWhite", Rand.Next(0.4F, 0.8F),
                        Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 3:
                    square.AddWorldInventoryItem(
                        "PaperclipBox", Rand.Next(0.4F, 0.8F),
                        Rand.Next(0.4F, 0.8F),
                        object.getSurfaceOffsetNoTable() / 96.0F);
                    break;
                  case 4:
                    square.AddWorldInventoryItem(
                        "RubberBand", Rand.Next(0.4F, 0.8F),
                        Rand.Next(0.4F, 0.8F),
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
        return sq.getRoom() != nullptr && "office" == sq.getRoom().getName());
  }

  /**
   * Description copied from class: RandomizedBuildingBase
   */
  bool isValid(BuildingDef def, bool force) {
    return def.getRoom("office") != nullptr || force;
  }

public
  RBOffice() {
    this.name = "Offices";
    this.setAlwaysDo(true);
  }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
