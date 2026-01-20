#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase/ZoneType.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedZoneStory {


class RZSForestCampEaten : public RandomizedZoneStoryBase {
public:
    public RZSForestCampEaten() {
      this.name = "Forest Camp Eaten";
      this.chance = 10;
      this.minZoneHeight = 6;
      this.minZoneWidth = 10;
      this.minimumDays = 30;
      this.zoneType.push_back(ZoneType.Forest);
   }

    void randomizeZoneStory(Zone var1) {
    int var2 = var1.pickedXForZoneStory;
    int var3 = var1.pickedYForZoneStory;
    std::vector var4 = RZSForestCamp.getForestClutter();
    std::vector var5 = RZSForestCamp.getCoolerClutter();
    std::vector var6 = RZSForestCamp.getFireClutter();
      this.cleanAreaForStory(this, var1);
      this.addTileObject(var2, var3, var1.z, "camping_01_6");
      this.addItemOnGround(this.getSq(var2, var3, var1.z), (std::string)var6.get(Rand.Next(var6.size())));
    int var7 = 0;
    uint8_t var8 = 0;
      this.addTentNorthSouth(var2 - 4, var3 + var8 - 2, var1.z);
      var7 += Rand.Next(1, 3);
      this.addTentNorthSouth(var2 - 3 + var7, var3 + var8 - 2, var1.z);
      var7 += Rand.Next(1, 3);
      this.addTentNorthSouth(var2 - 2 + var7, var3 + var8 - 2, var1.z);
      if (Rand.NextBool(1)) {
         var7 += Rand.Next(1, 3);
         this.addTentNorthSouth(var2 - 1 + var7, var3 + var8 - 2, var1.z);
      }

      if (Rand.NextBool(2)) {
         var7 += Rand.Next(1, 3);
         this.addTentNorthSouth(var2 + var7, var3 + var8 - 2, var1.z);
      }

    InventoryContainer var9 = (InventoryContainer)InventoryItemFactory.CreateItem("Base.Cooler");
    int var10 = Rand.Next(2, 5);

      for (int var11 = 0; var11 < var10; var11++) {
         var9.getItemContainer().AddItem((std::string)var5.get(Rand.Next(var5.size())));
      }

      this.addItemOnGround(this.getRandomFreeSquare(this, var1), var9);
      var10 = Rand.Next(3, 7);

      for (int var20 = 0; var20 < var10; var20++) {
         this.addItemOnGround(this.getRandomFreeSquare(this, var1), (std::string)var4.get(Rand.Next(var4.size())));
      }

    std::vector var21 = this.addZombiesOnSquare(1, "Camper", nullptr, this.getRandomFreeSquare(this, var1));
    IsoZombie var12 = var21.empty() ? nullptr : (IsoZombie)var21.get(0);
    int var13 = Rand.Next(3, 7);
    void* var14 = nullptr;

      for (int var15 = 0; var15 < var13; var15++) {
         var14 = createRandomDeadBody(this.getRandomFreeSquare(this, var1), nullptr, Rand.Next(5, 10), 0, "Camper");
         if (var14 != nullptr) {
            this.addBloodSplat(var14.getSquare(), 10);
         }
      }

      var14 = createRandomDeadBody(this.getSq(var2, var3 + 3, var1.z), nullptr, Rand.Next(5, 10), 0, "Camper");
      if (var14 != nullptr) {
         this.addBloodSplat(var14.getSquare(), 10);
         if (var12 != nullptr) {
            var12.faceLocationF(((IsoDeadBody)var14).x, ((IsoDeadBody)var14).y);
            var12.setX(((IsoDeadBody)var14).x + 1.0F);
            var12.setY(((IsoDeadBody)var14).y);
            var12.setEatBodyTarget((IsoMovingObject)var14, true);
         }
      }
   }
}
} // namespace randomizedZoneStory
} // namespace randomizedWorld
} // namespace zombie
