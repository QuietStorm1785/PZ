#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBOffice : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
    IsoCell var2 = IsoWorld.instance.CurrentCell;

      for (int var3 = var1.x - 1; var3 < var1.x2 + 1; var3++) {
         for (int var4 = var1.y - 1; var4 < var1.y2 + 1; var4++) {
            for (int var5 = 0; var5 < 8; var5++) {
    IsoGridSquare var6 = var2.getGridSquare(var3, var4, var5);
               if (var6 != nullptr && this.roomValid(var6)) {
                  for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var6.getObjects().get(var7);
                     if (var8.isTableSurface()
                        && Rand.NextBool(2)
                        && var6.getObjects().size() == 2
                        && var8.getProperties().Val("BedType") == nullptr
                        && var8.isTableSurface()
                        && (var8.getContainer() == nullptr || "desk" == var8.getContainer().getType()))) {
    int var9 = Rand.Next(0, 8);
                        switch (var9) {
                           case 0:
                              var6.AddWorldInventoryItem("Pen", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 1:
                              var6.AddWorldInventoryItem("Pencil", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 2:
                              var6.AddWorldInventoryItem("Crayons", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 3:
                              var6.AddWorldInventoryItem("RedPen", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 4:
                              var6.AddWorldInventoryItem("BluePen", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 5:
                              var6.AddWorldInventoryItem("Eraser", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                        }

    int var10 = Rand.Next(0, 6);
                        switch (var10) {
                           case 0:
                              var6.AddWorldInventoryItem("Doodle", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 1:
                              var6.AddWorldInventoryItem("Book", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 2:
                              var6.AddWorldInventoryItem("Notebook", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 3:
                              var6.AddWorldInventoryItem("SheetPaper2", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                        }

    int var11 = Rand.Next(0, 7);
                        switch (var11) {
                           case 0:
                              var6.AddWorldInventoryItem("MugRed", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 1:
                              var6.AddWorldInventoryItem("Mugl", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 2:
                              var6.AddWorldInventoryItem("MugWhite", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 3:
                              var6.AddWorldInventoryItem("PaperclipBox", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                              break;
                           case 4:
                              var6.AddWorldInventoryItem("RubberBand", Rand.Next(0.4F, 0.8F), Rand.Next(0.4F, 0.8F), var8.getSurfaceOffsetNoTable() / 96.0F);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    bool roomValid(IsoGridSquare var1) {
      return var1.getRoom() != nullptr && "office" == var1.getRoom().getName());
   }

    bool isValid(BuildingDef var1, bool var2) {
      return var1.getRoom("office") != nullptr || var2;
   }

    public RBOffice() {
      this.name = "Offices";
      this.setAlwaysDo(true);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
