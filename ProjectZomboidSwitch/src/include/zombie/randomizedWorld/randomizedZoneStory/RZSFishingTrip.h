#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase/ZoneType.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {


class RZSFishingTrip : public RandomizedZoneStoryBase {
public:
    public RZSFishingTrip() {
      this.name = "Fishing Trip";
      this.chance = 10;
      this.minZoneHeight = 8;
      this.minZoneWidth = 8;
      this.zoneType.push_back(ZoneType.Beach);
      this.zoneType.push_back(ZoneType.Lake);
   }

   public static std::vector<std::string> getFishes() {
    std::vector var0 = new std::vector();
      var0.push_back("Base.Catfish");
      var0.push_back("Base.Bass");
      var0.push_back("Base.Perch");
      var0.push_back("Base.Crappie");
      var0.push_back("Base.Panfish");
      var0.push_back("Base.Pike");
      var0.push_back("Base.Trout");
      var0.push_back("Base.BaitFish");
    return var0;
   }

   public static std::vector<std::string> getFishingTools() {
    std::vector var0 = new std::vector();
      var0.push_back("Base.FishingTackle");
      var0.push_back("Base.FishingTackle");
      var0.push_back("Base.FishingTackle2");
      var0.push_back("Base.FishingTackle2");
      var0.push_back("Base.FishingLine");
      var0.push_back("Base.FishingLine");
      var0.push_back("Base.FishingNet");
      var0.push_back("Base.Worm");
      var0.push_back("Base.Worm");
      var0.push_back("Base.Worm");
      var0.push_back("Base.Worm");
    return var0;
   }

    void randomizeZoneStory(Zone var1) {
    std::vector var2 = getFishes();
    std::vector var3 = getFishingTools();
      this.cleanAreaForStory(this, var1);
      this.addVehicle(var1, this.getSq(var1.x, var1.y, var1.z), nullptr, nullptr, "Base.PickUpTruck", nullptr, nullptr, "Fisherman");
    int var4 = Rand.Next(1, 3);

      for (int var5 = 0; var5 < var4; var5++) {
         this.addTileObject(this.getRandomFreeSquare(this, var1), "furniture_seating_outdoor_01_" + Rand.Next(16, 20));
      }

    InventoryContainer var9 = (InventoryContainer)InventoryItemFactory.CreateItem("Base.Cooler");
    int var6 = Rand.Next(4, 10);

      for (int var7 = 0; var7 < var6; var7++) {
         var9.getItemContainer().AddItem((std::string)var2.get(Rand.Next(var2.size())));
      }

      this.addItemOnGround(this.getRandomFreeSquare(this, var1), var9);
    InventoryContainer var12 = (InventoryContainer)InventoryItemFactory.CreateItem("Base.Toolbox");
      var6 = Rand.Next(3, 8);

      for (int var8 = 0; var8 < var6; var8++) {
         var12.getItemContainer().AddItem((std::string)var3.get(Rand.Next(var3.size())));
      }

      this.addItemOnGround(this.getRandomFreeSquare(this, var1), var12);
      var6 = Rand.Next(2, 5);

      for (int var13 = 0; var13 < var6; var13++) {
         this.addItemOnGround(this.getRandomFreeSquare(this, var1), "FishingRod");
      }

      this.addZombiesOnSquare(Rand.Next(2, 5), "Fisherman", 0, this.getRandomFreeSquare(this, var1));
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
