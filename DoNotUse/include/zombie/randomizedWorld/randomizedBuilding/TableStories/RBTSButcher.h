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


class RBTSButcher : public RBTableStoryBase {
public:
    public RBTSButcher() {
      this.chance = 3;
      this.ignoreAgainstWall = true;
      this.rooms.push_back("livingroom");
      this.rooms.push_back("kitchen");
   }

    void randomizeBuilding(BuildingDef var1) {
    std::string var2 = "Base.DeadRabbit";
    std::string var3 = "Base.Rabbitmeat";
    int var4 = Rand.Next(0, 4);
      switch (var4) {
         case 0:
            var2 = "Base.DeadBird";
            var3 = "Base.Smallbirdmeat";
            break;
         case 1:
            var2 = "Base.DeadSquirrel";
            var3 = "Base.Smallanimalmeat";
            break;
         case 2:
            var2 = "Base.Panfish";
            var3 = "Base.FishFillet";
            break;
         case 3:
            var2 = "Base.BaitFish";
            var3 = "Base.FishFillet";
            break;
         case 4:
            var2 = "Base.Catfish";
            var3 = "Base.FishFillet";
      }

      this.addWorldItem(var2, this.table1.getSquare(), 0.453F, 0.64F, this.table1.getSurfaceOffsetNoTable() / 96.0F, 1);
      this.addWorldItem(var3, this.table1.getSquare(), 0.835F, 0.851F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
      this.addWorldItem("Base.KitchenKnife", this.table1.getSquare(), 0.742F, 0.445F, this.table1.getSurfaceOffsetNoTable() / 96.0F);
   }
}
} // namespace TableStories
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
