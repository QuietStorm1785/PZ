#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
namespace TableStories {


class RBTSDrink : public RBTableStoryBase {
public:
    public RBTSDrink() {
      this.chance = 7;
      this.rooms.push_back("livingroom");
      this.rooms.push_back("kitchen");
   }

    void randomizeBuilding(BuildingDef var1) {
      this.addWorldItem(this.getDrink(), this.table1.getSquare(), 0.539F, 0.742F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      if (Rand.Next(70) < 100) {
         this.addWorldItem(this.getDrink(), this.table1.getSquare(), 0.734F, 0.797F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      }

      if (Rand.Next(70) < 100) {
         this.addWorldItem(this.getDrink(), this.table1.getSquare(), 0.554F, 0.57F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      }

      if (Rand.Next(70) < 100) {
         this.addWorldItem(this.getDrink(), this.table1.getSquare(), 0.695F, 0.336F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      }

      if (Rand.Next(70) < 100) {
         this.addWorldItem(this.getDrink(), this.table1.getSquare(), 0.875F, 0.687F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      }

      if (Rand.Next(70) < 100) {
         this.addWorldItem(this.getDrink(), this.table1.getSquare(), 0.476F, 0.273F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      }

      this.addWorldItem("Base.PlasticCup", this.table1.getSquare(), 0.843F, 0.531F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
    std::string var2 = "Base.Crisps";
    int var3 = Rand.Next(0, 4);
      switch (var3) {
         case 0:
            var2 = "Base.Crisps2";
            break;
         case 1:
            var2 = "Base.Crisps3";
            break;
         case 2:
            var2 = "Base.Crisps4";
      }

      this.addWorldItem(var2, this.table1.getSquare(), 0.87F, 0.86F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      if (Rand.Next(70) < 100) {
         this.addWorldItem("Base.Cigarettes", this.table1.getSquare(), 0.406F, 0.843F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      }

      if (Rand.Next(70) < 100) {
         this.addWorldItem("Base.Cigarettes", this.table1.getSquare(), 0.578F, 0.953F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      }
   }

    std::string getDrink() {
      if (Rand.NextBool(5)) {
         return "Base.PlasticCup";
      } else {
    int var1 = Rand.Next(0, 4);
         switch (var1) {
            case 0:
               return "Base.BeerBottle";
            case 1:
               return "Base.BeerEmpty";
            case 2:
               return "Base.BeerCan";
            case 3:
               return "Base.BeerCanEmpty";
            default:
               return "Base.BeerBottle";
         }
      }
   }
}
} // namespace TableStories
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
