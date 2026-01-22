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


class RDSDeadDrunk : public RandomizedDeadSurvivorBase {
public:
   const std::vector<std::string> alcoholList = std::make_unique<std::vector<>>();

    public RDSDeadDrunk() {
      this.name = "Dead Drunk";
      this.setChance(10);
      this.alcoholList.push_back("Base.WhiskeyFull");
      this.alcoholList.push_back("Base.WhiskeyEmpty");
      this.alcoholList.push_back("Base.Wine");
      this.alcoholList.push_back("Base.WineEmpty");
      this.alcoholList.push_back("Base.Wine2");
      this.alcoholList.push_back("Base.WineEmpty2");
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
    IsoDeadBody var3 = RandomizedDeadSurvivorBase.createRandomDeadBody(var2, 0);
      if (var3 != nullptr) {
    int var4 = Rand.Next(2, 4);

         for (int var5 = 0; var5 < var4; var5++) {
    InventoryItem var6 = InventoryItemFactory.CreateItem(this.alcoholList.get(Rand.Next(0, this.alcoholList.size())));
            var3.getSquare().AddWorldInventoryItem(var6, Rand.Next(0.5F, 1.0F), Rand.Next(0.5F, 1.0F), 0.0F);
            var1.bAlarmed = false;
         }

         var3.setPrimaryHandItem(InventoryItemFactory.CreateItem("Base.WhiskeyEmpty"));
      }
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
