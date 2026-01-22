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


class RBTSElectronics : public RBTableStoryBase {
public:
    public RBTSElectronics() {
      this.chance = 5;
      this.rooms.push_back("livingroom");
      this.rooms.push_back("kitchen");
      this.rooms.push_back("bedroom");
   }

    void randomizeBuilding(BuildingDef var1) {
    std::string var2 = "Base.ElectronicsMag1";
    int var3 = Rand.Next(0, 4);
      switch (var3) {
         case 0:
            var2 = "Base.ElectronicsMag2";
            break;
         case 1:
            var2 = "Base.ElectronicsMag3";
            break;
         case 2:
            var2 = "Base.ElectronicsMag5";
      }

      this.addWorldItem(var2, this.table1.getSquare(), 0.36F, 0.789F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      this.addWorldItem("Base.ElectronicsScrap", this.table1.getSquare(), 0.71F, 0.82F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      this.addWorldItem("Base.Screwdriver", this.table1.getSquare(), 0.36F, 0.421F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      var2 = "Radio.CDPlayer";
      var3 = Rand.Next(0, 6);
      switch (var3) {
         case 0:
            var2 = "Base.Torch";
            break;
         case 1:
            var2 = "Base.Remote";
            break;
         case 2:
            var2 = "Base.VideoGame";
            break;
         case 3:
            var2 = "Base.CordlessPhone";
            break;
         case 4:
            var2 = "Base.Headphones";
      }

      this.addWorldItem(var2, this.table1.getSquare(), 0.695F, 0.43F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
   }
}
} // namespace TableStories
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
