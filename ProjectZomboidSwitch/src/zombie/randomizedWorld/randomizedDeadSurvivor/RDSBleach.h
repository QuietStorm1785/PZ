#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSBleach : public RandomizedDeadSurvivorBase {
public:
    public RDSBleach() {
      this.name = "Suicide by Bleach";
      this.setChance(10);
      this.setMinimumDays(60);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
    IsoDeadBody var3 = RandomizedDeadSurvivorBase.createRandomDeadBody(var2, 0);
      if (var3 != nullptr) {
    int var4 = Rand.Next(1, 3);

         for (int var5 = 0; var5 < var4; var5++) {
    InventoryItem var6 = InventoryItemFactory.CreateItem("Base.BleachEmpty");
            var3.getSquare().AddWorldInventoryItem(var6, Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), 0.0F);
         }

         var3.setPrimaryHandItem(InventoryItemFactory.CreateItem("Base.BleachEmpty"));
         var1.bAlarmed = false;
      }
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
