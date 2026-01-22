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
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase/ZoneType.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {


class RZSBBQParty : public RandomizedZoneStoryBase {
public:
    public RZSBBQParty() {
      this.name = "BBQ Party";
      this.chance = 10;
      this.minZoneHeight = 12;
      this.minZoneWidth = 12;
      this.zoneType.push_back(ZoneType.Beach);
      this.zoneType.push_back(ZoneType.Lake);
   }

   public static std::vector<std::string> getBeachClutter() {
    std::vector var0 = new std::vector();
      var0.push_back("Base.Crisps");
      var0.push_back("Base.Crisps3");
      var0.push_back("Base.MuttonChop");
      var0.push_back("Base.PorkChop");
      var0.push_back("Base.Steak");
      var0.push_back("Base.Pop");
      var0.push_back("Base.BeerBottle");
      var0.push_back("Base.BeerBottle");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
      var0.push_back("Base.BeerCan");
    return var0;
   }

    void randomizeZoneStory(Zone var1) {
    int var2 = var1.pickedXForZoneStory;
    int var3 = var1.pickedYForZoneStory;
    std::vector var4 = getBeachClutter();
    std::vector var5 = RZSForestCamp.getCoolerClutter();
    IsoGridSquare var6 = this.getSq(var2, var3, var1.z);
    IsoBarbecue var7 = std::make_shared<IsoBarbecue>(IsoWorld.instance.getCell(), var6, (IsoSprite)IsoSpriteManager.instance.NamedMap.get("appliances_cooking_01_35"));
      var6.getObjects().push_back(var7);
    int var8 = Rand.Next(1, 4);

      for (int var9 = 0; var9 < var8; var9++) {
         this.addTileObject(this.getRandomFreeSquare(this, var1), "furniture_seating_outdoor_01_" + Rand.Next(16, 20));
      }

    InventoryContainer var13 = (InventoryContainer)InventoryItemFactory.CreateItem("Base.Cooler");
    int var10 = Rand.Next(4, 8);

      for (int var11 = 0; var11 < var10; var11++) {
         var13.getItemContainer().AddItem((std::string)var5.get(Rand.Next(var5.size())));
      }

      this.addItemOnGround(this.getRandomFreeSquare(this, var1), var13);
      var10 = Rand.Next(3, 7);

      for (int var15 = 0; var15 < var10; var15++) {
         this.addItemOnGround(this.getRandomFreeSquare(this, var1), (std::string)var4.get(Rand.Next(var4.size())));
      }

    int var16 = Rand.Next(3, 8);

      for (int var12 = 0; var12 < var16; var12++) {
         this.addZombiesOnSquare(1, "Tourist", nullptr, this.getRandomFreeSquare(this, var1));
      }
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
