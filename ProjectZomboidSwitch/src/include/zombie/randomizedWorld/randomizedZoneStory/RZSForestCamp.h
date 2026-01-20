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


class RZSForestCamp : public RandomizedZoneStoryBase {
public:
    public RZSForestCamp() {
      this.name = "Basic Forest Camp";
      this.chance = 10;
      this.minZoneHeight = 6;
      this.minZoneWidth = 6;
      this.zoneType.push_back(ZoneType.Forest);
   }

   public static std::vector<std::string> getForestClutter() {
    std::vector var0 = new std::vector();
      var0.push_back("Base.Crisps");
      var0.push_back("Base.Crisps2");
      var0.push_back("Base.Crisps3");
      var0.push_back("Base.Crisps4");
      var0.push_back("Base.Pop");
      var0.push_back("Base.Pop2");
      var0.push_back("Base.WaterBottleFull");
      var0.push_back("Base.CannedSardines");
      var0.push_back("Base.CannedChili");
      var0.push_back("Base.CannedBolognese");
      var0.push_back("Base.CannedCornedBeef");
      var0.push_back("Base.TinnedSoup");
      var0.push_back("Base.TinnedBeans");
      var0.push_back("Base.TunaTin");
      var0.push_back("Base.WhiskeyFull");
      var0.push_back("Base.BeerBottle");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
    return var0;
   }

   public static std::vector<std::string> getCoolerClutter() {
    std::vector var0 = new std::vector();
      var0.push_back("Base.Pop");
      var0.push_back("Base.Pop2");
      var0.push_back("Base.BeefJerky");
      var0.push_back("Base.Ham");
      var0.push_back("Base.WaterBottleFull");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
    return var0;
   }

   public static std::vector<std::string> getFireClutter() {
    std::vector var0 = new std::vector();
      var0.push_back("Base.WaterPotRice");
      var0.push_back("Base.WaterPot");
      var0.push_back("Base.Pot");
      var0.push_back("Base.WaterSaucepanRice");
      var0.push_back("Base.WaterSaucepanPasta");
      var0.push_back("Base.PotOfStew");
    return var0;
   }

    void randomizeZoneStory(Zone var1) {
    int var2 = var1.pickedXForZoneStory;
    int var3 = var1.pickedYForZoneStory;
    std::vector var4 = getForestClutter();
    std::vector var5 = getCoolerClutter();
    std::vector var6 = getFireClutter();
      this.cleanAreaForStory(this, var1);
      this.addTileObject(var2, var3, var1.z, "camping_01_6");
      this.addItemOnGround(this.getSq(var2, var3, var1.z), (std::string)var6.get(Rand.Next(var6.size())));
    int var7 = Rand.Next(-1, 2);
    int var8 = Rand.Next(-1, 2);
      this.addTentWestEast(var2 + var7 - 2, var3 + var8, var1.z);
      if (Rand.Next(100) < 70) {
         this.addTentNorthSouth(var2 + var7, var3 + var8 - 2, var1.z);
      }

      if (Rand.Next(100) < 30) {
         this.addTentNorthSouth(var2 + var7 + 1, var3 + var8 - 2, var1.z);
      }

      this.addTileObject(var2 + 2, var3, var1.z, "furniture_seating_outdoor_01_19");
    InventoryContainer var9 = (InventoryContainer)InventoryItemFactory.CreateItem("Base.Cooler");
    int var10 = Rand.Next(2, 5);

      for (int var11 = 0; var11 < var10; var11++) {
         var9.getItemContainer().AddItem((std::string)var5.get(Rand.Next(var5.size())));
      }

      this.addItemOnGround(this.getRandomFreeSquare(this, var1), var9);
      var10 = Rand.Next(3, 7);

      for (int var13 = 0; var13 < var10; var13++) {
         this.addItemOnGround(this.getRandomFreeSquare(this, var1), (std::string)var4.get(Rand.Next(var4.size())));
      }

      this.addZombiesOnSquare(Rand.Next(1, 3), "Camper", nullptr, this.getRandomFreeSquare(this, var1));
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
