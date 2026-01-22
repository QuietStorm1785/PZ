#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBLooted : public RandomizedBuildingBase {
public:
    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
    IsoCell var2 = IsoWorld.instance.CurrentCell;

      for (int var3 = var1.x - 1; var3 < var1.x2 + 1; var3++) {
         for (int var4 = var1.y - 1; var4 < var1.y2 + 1; var4++) {
            for (int var5 = 0; var5 < 8; var5++) {
    IsoGridSquare var6 = var2.getGridSquare(var3, var4, var5);
               if (var6 != nullptr) {
                  for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var6.getObjects().get(var7);
                     if (Rand.Next(100) >= 85 && dynamic_cast<IsoDoor*>(var8) != nullptr && ((IsoDoor)var8).isExteriorDoor(nullptr)) {
                        ((IsoDoor)var8).destroy();
                     }

                     if (Rand.Next(100) >= 85 && dynamic_cast<IsoWindow*>(var8) != nullptr) {
                        ((IsoWindow)var8).smashWindow(false, false);
                     }

                     if (var8.getContainer() != nullptr && var8.getContainer().getItems() != nullptr) {
                        for (int var9 = 0; var9 < var8.getContainer().getItems().size(); var9++) {
                           if (Rand.Next(100) < 80) {
                              var8.getContainer().getItems().remove(var9);
                              var9--;
                           }
                        }

                        ItemPickerJava.updateOverlaySprite(var8);
                        var8.getContainer().setExplored(true);
                     }
                  }
               }
            }
         }
      }

      var1.setAllExplored(true);
      var1.bAlarmed = false;
   }

    public RBLooted() {
      this.name = "Looted";
      this.setChance(10);
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
