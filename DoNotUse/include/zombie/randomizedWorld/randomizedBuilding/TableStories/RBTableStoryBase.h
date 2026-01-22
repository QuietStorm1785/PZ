#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/randomizedWorld/randomizedBuilding/RandomizedBuildingBase.h"
#include <iterator>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
namespace TableStories {


class RBTableStoryBase : public RandomizedBuildingBase {
public:
   public static std::vector<RBTableStoryBase> allStories = std::make_unique<std::vector<>>();
    static int totalChance = 0;
    int chance = 0;
   protected std::vector<std::string> rooms = std::make_unique<std::vector<>>();
    bool need2Tables = false;
    bool ignoreAgainstWall = false;
    IsoObject table2 = nullptr;
    IsoObject table1 = nullptr;
    bool westTable = false;
   private static const std::unordered_map<RBTableStoryBase, int> rbtsmap = std::make_unique<std::unordered_map<>>();
   private static const std::vector<IsoObject> tableObjects = std::make_unique<std::vector<>>();
   public std::vector<std::unordered_map<std::string, int>> fullTableMap = std::make_unique<std::vector<>>();

    static void initStories(IsoGridSquare var0, IsoObject var1) {
      if (allStories.empty()) {
         allStories.push_back(std::make_unique<RBTSBreakfast>());
         allStories.push_back(std::make_unique<RBTSDinner>());
         allStories.push_back(std::make_unique<RBTSSoup>());
         allStories.push_back(std::make_unique<RBTSSewing>());
         allStories.push_back(std::make_unique<RBTSElectronics>());
         allStories.push_back(std::make_unique<RBTSFoodPreparation>());
         allStories.push_back(std::make_unique<RBTSButcher>());
         allStories.push_back(std::make_unique<RBTSSandwich>());
         allStories.push_back(std::make_unique<RBTSDrink>());
      }

      totalChance = 0;
      rbtsmap.clear();

      for (int var2 = 0; var2 < allStories.size(); var2++) {
    RBTableStoryBase var3 = allStories.get(var2);
         if (var3.isValid(var0, var1, false) && var3.isTimeValid(false)) {
            totalChance = totalChance + var3.chance;
            rbtsmap.put(var3, var3.chance);
         }
      }
   }

    static RBTableStoryBase getRandomStory(IsoGridSquare var0, IsoObject var1) {
      initStories(var0, var1);
    int var2 = Rand.Next(totalChance);
    Iterator var3 = rbtsmap.keySet().iterator();
    int var4 = 0;

      while (var3.hasNext()) {
    RBTableStoryBase var5 = (RBTableStoryBase)var3.next();
         var4 += rbtsmap.get(var5);
         if (var2 < var4) {
            var5.table1 = var1;
    return var5;
         }
      }

    return nullptr;
   }

    bool isValid(IsoGridSquare var1, IsoObject var2, bool var3) {
      if (var3) {
    return true;
      } else if (this.rooms != nullptr && var1.getRoom() != nullptr && !this.rooms.contains(var1.getRoom().getName())) {
    return false;
      } else {
         if (this.need2Tables) {
            this.table2 = this.getSecondTable(var2);
            if (this.table2 == nullptr) {
    return false;
            }
         }

         return !this.ignoreAgainstWall || !var1.getWallFull();
      }
   }

    IsoObject getSecondTable(IsoObject var1) {
      this.westTable = true;
    IsoGridSquare var2 = var1.getSquare();
      if (this.ignoreAgainstWall && var2.getWallFull()) {
    return nullptr;
      } else {
         var1.getSpriteGridObjects(tableObjects);
    IsoGridSquare var3 = var2.getAdjacentSquare(IsoDirections.W);
    IsoObject var4 = this.checkForTable(var3, var1, tableObjects);
         if (var4 == nullptr) {
            var3 = var2.getAdjacentSquare(IsoDirections.E);
            var4 = this.checkForTable(var3, var1, tableObjects);
         }

         if (var4 == nullptr) {
            this.westTable = false;
         }

         if (var4 == nullptr) {
            var3 = var2.getAdjacentSquare(IsoDirections.N);
            var4 = this.checkForTable(var3, var1, tableObjects);
         }

         if (var4 == nullptr) {
            var3 = var2.getAdjacentSquare(IsoDirections.S);
            var4 = this.checkForTable(var3, var1, tableObjects);
         }

         return var4 != nullptr && this.ignoreAgainstWall && var3.getWallFull() ? nullptr : var4;
      }
   }

    IsoObject checkForTable(IsoGridSquare var1, IsoObject var2, std::vector<IsoObject> var3) {
      if (var1 == nullptr) {
    return nullptr;
      } else if (var1.isSomethingTo(var2.getSquare())) {
    return nullptr;
      } else {
         for (int var4 = 0; var4 < var1.getObjects().size(); var4++) {
    IsoObject var5 = (IsoObject)var1.getObjects().get(var4);
            if ((var3.empty() || var3.contains(var5)) && var5.getProperties().isTable() && var5.getContainer() == nullptr && var5 != var2) {
    return var5;
            }
         }

    return nullptr;
      }
   }
}
} // namespace TableStories
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
