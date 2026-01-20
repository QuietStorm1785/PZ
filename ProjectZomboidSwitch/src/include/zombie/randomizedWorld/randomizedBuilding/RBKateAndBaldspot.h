#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBKateAndBaldspot : public RandomizedBuildingBase {
public:
    public RBKateAndBaldspot() {
      this.name = "K&B story";
      this.setChance(0);
      this.setUnique(true);
   }

    void randomizeBuilding(BuildingDef var1) {
      var1.bAlarmed = false;
      var1.setHasBeenVisited(true);
      var1.setAllExplored(true);
    std::vector var2 = this.addZombiesOnSquare(1, "Kate", 100, this.getSq(10746, 9412, 1));
      if (var2 != nullptr && !var2.empty()) {
    IsoZombie var3 = (IsoZombie)var2.get(0);
    HumanVisual var4 = (HumanVisual)var3.getVisual();
         var4.setHairModel("Rachel");
         var4.setHairColor(std::make_shared<ImmutableColor>(0.83F, 0.67F, 0.27F));

         for (int var5 = 0; var5 < var3.getItemVisuals().size(); var5++) {
    ItemVisual var6 = (ItemVisual)var3.getItemVisuals().get(var5);
            if (var6.getClothingItemName() == "Skirt_Knees")) {
               var6.setTint(std::make_shared<ImmutableColor>(0.54F, 0.54F, 0.54F));
            }
         }

         var3.getHumanVisual().setSkinTextureIndex(1);
         var3.addBlood(BloodBodyPartType.LowerLeg_L, true, true, true);
         var3.addBlood(BloodBodyPartType.LowerLeg_L, true, true, true);
         var3.addBlood(BloodBodyPartType.UpperLeg_L, true, true, true);
         var3.addBlood(BloodBodyPartType.UpperLeg_L, true, true, true);
         var3.setCrawler(true);
         var3.setCanWalk(false);
         var3.setCrawlerType(1);
         var3.resetModelNextFrame();
         var2 = this.addZombiesOnSquare(1, "Bob", 0, this.getSq(10747, 9412, 1));
         if (var2 != nullptr && !var2.empty()) {
    IsoZombie var19 = (IsoZombie)var2.get(0);
            var4 = (HumanVisual)var19.getVisual();
            var4.setHairModel("Baldspot");
            var4.setHairColor(std::make_shared<ImmutableColor>(0.337F, 0.173F, 0.082F));
            var4.setBeardModel("");

            for (int var20 = 0; var20 < var19.getItemVisuals().size(); var20++) {
    ItemVisual var7 = (ItemVisual)var19.getItemVisuals().get(var20);
               if (var7.getClothingItemName() == "Trousers_DefaultTEXTURE_TINT")) {
                  var7.setTint(std::make_shared<ImmutableColor>(0.54F, 0.54F, 0.54F));
               }

               if (var7.getClothingItemName() == "Shirt_FormalTINT")) {
                  var7.setTint(std::make_shared<ImmutableColor>(0.63F, 0.71F, 0.82F));
               }
            }

            var19.getHumanVisual().setSkinTextureIndex(1);
            var19.resetModelNextFrame();
            var19.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("KatePic"));
            var19.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("RippedSheets"));
            var19.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("Pills"));
    InventoryItem var21 = InventoryItemFactory.CreateItem("Hammer");
            var21.setCondition(1);
            var19.addItemToSpawnAtDeath(var21);
            var19.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("Nails"));
            var19.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("Plank"));
            var2 = this.addZombiesOnSquare(1, "Raider", 0, this.getSq(10745, 9411, 0));
            if (var2 != nullptr && !var2.empty()) {
    IsoZombie var22 = (IsoZombie)var2.get(0);
               var4 = (HumanVisual)var22.getVisual();
               var4.setHairModel("Crewcut");
               var4.setHairColor(std::make_shared<ImmutableColor>(0.37F, 0.27F, 0.23F));
               var4.setBeardModel("Goatee");

               for (int var8 = 0; var8 < var22.getItemVisuals().size(); var8++) {
    ItemVisual var9 = (ItemVisual)var22.getItemVisuals().get(var8);
                  if (var9.getClothingItemName() == "Trousers_DefaultTEXTURE_TINT")) {
                     var9.setTint(std::make_shared<ImmutableColor>(0.54F, 0.54F, 0.54F));
                  }

                  if (var9.getClothingItemName() == "Vest_DefaultTEXTURE_TINT")) {
                     var9.setTint(std::make_shared<ImmutableColor>(0.22F, 0.25F, 0.27F));
                  }
               }

               var22.getHumanVisual().setSkinTextureIndex(1);
    InventoryItem var23 = InventoryItemFactory.CreateItem("Shotgun");
               var23.setCondition(0);
               var22.setAttachedItem("Rifle On Back", var23);
    InventoryItem var24 = InventoryItemFactory.CreateItem("BaseballBat");
               var24.setCondition(1);
               var22.addItemToSpawnAtDeath(var24);
               var22.addItemToSpawnAtDeath(InventoryItemFactory.CreateItem("ShotgunShells"));
               var22.resetModelNextFrame();
               this.addItemOnGround(this.getSq(10747, 9412, 1), InventoryItemFactory.CreateItem("Pillow"));
    IsoGridSquare var10 = this.getSq(10745, 9410, 0);
               var10.Burn();
               var10 = this.getSq(10745, 9411, 0);
               var10.Burn();
               var10 = this.getSq(10746, 9411, 0);
               var10.Burn();
               var10 = this.getSq(10745, 9410, 0);
               var10.Burn();
               var10 = this.getSq(10745, 9412, 0);
               var10.Burn();
               var10 = this.getSq(10747, 9410, 0);
               var10.Burn();
               var10 = this.getSq(10746, 9409, 0);
               var10.Burn();
               var10 = this.getSq(10745, 9409, 0);
               var10.Burn();
               var10 = this.getSq(10744, 9410, 0);
               var10.Burn();
               var10 = this.getSq(10747, 9411, 0);
               var10.Burn();
               var10 = this.getSq(10746, 9412, 0);
               var10.Burn();
    IsoGridSquare var11 = this.getSq(10746, 9410, 0);

               for (int var12 = 0; var12 < var11.getObjects().size(); var12++) {
    IsoObject var13 = (IsoObject)var11.getObjects().get(var12);
                  if (var13.getContainer() != nullptr) {
    InventoryItem var14 = InventoryItemFactory.CreateItem("PotOfSoup");
                     var14.setCooked(true);
                     var14.setBurnt(true);
                     var13.getContainer().AddItem(var14);
                     break;
                  }
               }

               this.addBarricade(this.getSq(10747, 9417, 0), 3);
               this.addBarricade(this.getSq(10745, 9417, 0), 3);
               this.addBarricade(this.getSq(10744, 9413, 0), 3);
               this.addBarricade(this.getSq(10744, 9412, 0), 3);
               this.addBarricade(this.getSq(10752, 9413, 0), 3);
            }
         }
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
      this.debugLine = "";
      if (var1.x == 10744 && var1.y == 9409) {
    return true;
      } else {
         this.debugLine = "Need to be the K&B house";
    return false;
      }
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
