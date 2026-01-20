#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBTableStory/StoryDef.h"
#include "zombie/randomizedWorld/randomizedBuilding/RBTableStory/StorySpawnItem.h"
#include <algorithm>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBTableStory : public RandomizedBuildingBase {
public:
   public static std::vector<StoryDef> allStories = std::make_unique<std::vector<>>();
    float xOffset = 0.0F;
    float yOffset = 0.0F;
    IsoGridSquare currentSquare = nullptr;
   public std::vector<std::unordered_map<std::string, int>> fullTableMap = std::make_unique<std::vector<>>();
    IsoObject table1 = nullptr;
    IsoObject table2 = nullptr;

    void initStories() {
      if (allStories.empty()) {
    std::vector var1 = new std::vector();
         var1.push_back("livingroom");
         var1.push_back("kitchen");
    std::vector var2 = new std::vector();
    LinkedHashMap var3 = std::make_shared<LinkedHashMap>();
         var3.put("BakingPan", 50);
         var3.put("CakePrep", 50);
         var2.push_back(std::make_shared<StorySpawnItem>(this, var3, nullptr, 100));
         var2.push_back(std::make_shared<StorySpawnItem>(this, nullptr, "Chocolate", 100));
         var2.push_back(std::make_shared<StorySpawnItem>(this, nullptr, "Butter", 70));
         var2.push_back(std::make_shared<StorySpawnItem>(this, nullptr, "Flour", 70));
         var2.push_back(std::make_shared<StorySpawnItem>(this, nullptr, "Spoon", 100));
         var2.push_back(std::make_shared<StorySpawnItem>(this, nullptr, "EggCarton", 100));
         var2.push_back(std::make_shared<StorySpawnItem>(this, nullptr, "Egg", 100));
         allStories.push_back(std::make_shared<StoryDef>(this, var2, var1));
      }
   }

    bool isValid(BuildingDef var1, bool var2) {
    return false;
   }

    void randomizeBuilding(BuildingDef var1) {
      this.initStories();
      if (this.table1 != nullptr && this.table2 != nullptr) {
         if (this.table1.getSquare() != nullptr && this.table1.getSquare().getRoom() != nullptr) {
    std::vector var2 = new std::vector();

            for (int var3 = 0; var3 < allStories.size(); var3++) {
    StoryDef var4 = allStories.get(var3);
               if (var4.rooms == nullptr || var4.rooms.contains(this.table1.getSquare().getRoom().getName())) {
                  var2.push_back(var4);
               }
            }

            if (!var2.empty()) {
    StoryDef var13 = (StoryDef)var2.get(Rand.Next(0, var2.size()));
               if (var13 != nullptr) {
    bool var14 = true;
                  if ((int)this.table1.getY() != (int)this.table2.getY()) {
                     var14 = false;
                  }

                  this.doSpawnTable(var13.items, var14);
                  if (var13.addBlood) {
    int var5 = (int)this.table1.getX() - 1;
    int var6 = (int)this.table1.getX() + 1;
    int var7 = (int)this.table1.getY() - 1;
    int var8 = (int)this.table2.getY() + 1;
                     if (var14) {
                        var5 = (int)this.table1.getX() - 1;
                        var6 = (int)this.table2.getX() + 1;
                        var7 = (int)this.table1.getY() - 1;
                        var8 = (int)this.table2.getY() + 1;
                     }

                     for (int var9 = var5; var9 < var6 + 1; var9++) {
                        for (int var10 = var7; var10 < var8 + 1; var10++) {
    int var11 = Rand.Next(7, 15);

                           for (int var12 = 0; var12 < var11; var12++) {
                              this.currentSquare
                                 .getChunk()
                                 .addBloodSplat(var9 + Rand.Next(-0.5F, 0.5F), var10 + Rand.Next(-0.5F, 0.5F), this.table1.getZ(), Rand.Next(8));
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void doSpawnTable(std::vector<StorySpawnItem> var1, bool var2) {
      this.xOffset = 0.0F;
      this.yOffset = 0.0F;
    int var3 = 0;
      if (var2) {
         this.xOffset = 0.6F;
         this.yOffset = Rand.Next(0.5F, 1.1F);
      } else {
         this.yOffset = 0.6F;
         this.xOffset = Rand.Next(0.5F, 1.1F);
      }

      for (this.currentSquare = this.table1.getSquare(); var3 < var1.size(); var3++) {
    StorySpawnItem var4 = (StorySpawnItem)var1.get(var3);
    std::string var5 = this.getItemFromSSI(var4);
         if (var5 != nullptr) {
    InventoryItem var6 = this.currentSquare.AddWorldInventoryItem(var5, this.xOffset, this.yOffset, 0.4F);
            if (var6 != nullptr) {
               this.increaseOffsets(var2, var4);
            }
         }
      }
   }

    void increaseOffsets(bool var1, StorySpawnItem var2) {
    float var3 = 0.15F + var2.forcedOffset;
      if (var1) {
         this.xOffset += var3;
         if (this.xOffset > 1.0F) {
            this.currentSquare = this.table2.getSquare();
            this.xOffset = 0.35F;
         }

    float var4 = this.yOffset;

         while (Math.abs(var4 - this.yOffset) < 0.11F) {
            this.yOffset = Rand.Next(0.5F, 1.1F);
         }
      } else {
         this.yOffset += var3;
         if (this.yOffset > 1.0F) {
            this.currentSquare = this.table2.getSquare();
            this.yOffset = 0.35F;
         }

    float var5 = this.xOffset;

         while (Math.abs(var5 - this.xOffset) < 0.11F) {
            this.xOffset = Rand.Next(0.5F, 1.1F);
         }
      }
   }

    std::string getItemFromSSI(StorySpawnItem var1) {
      if (Rand.Next(100) > var1.chanceToSpawn) {
    return nullptr;
      } else if (var1.eitherObject != nullptr && !var1.eitherObject.empty()) {
    int var2 = Rand.Next(100);
    int var3 = 0;

         for (std::string var5 : var1.eitherObject.keySet()) {
    int var6 = (int)var1.eitherObject.get(var5);
            var3 += var6;
            if (var3 >= var2) {
    return var5;
            }
         }

    return nullptr;
      } else {
         return var1.object;
      }
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
