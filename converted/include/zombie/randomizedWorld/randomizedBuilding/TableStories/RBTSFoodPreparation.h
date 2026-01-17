#pragma once
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {
namespace TableStories {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RBTSFoodPreparation : public RBTableStoryBase {
public:
public
  RBTSFoodPreparation() {
    this.chance = 8;
    this.ignoreAgainstWall = true;
    this.rooms.add("livingroom");
    this.rooms.add("kitchen");
  }

  void randomizeBuilding(BuildingDef var1) {
    this.addWorldItem("Base.BakingTray", this.table1.getSquare(), 0.695F,
                      0.648F, this.table1.getSurfaceOffsetNoTable() / 96.0F, 1);
    std::string string = "Base.Chicken";
    int int0 = Rand.Next(0, 4);
    switch (int0) {
    case 0:
      string = "Base.Steak";
      break;
    case 1:
      string = "Base.MuttonChop";
      break;
    case 2:
      string = "Base.Smallbirdmeat";
    }

    this.addWorldItem(string, this.table1.getSquare(), 0.531F, 0.625F,
                      this.table1.getSurfaceOffsetNoTable() / 96.0F);
    this.addWorldItem(string, this.table1.getSquare(), 0.836F, 0.627F,
                      this.table1.getSurfaceOffsetNoTable() / 96.0F);
    this.addWorldItem(Rand.NextBool(2) ? "Base.Pepper" : "Base.Salt",
                      this.table1.getSquare(), 0.492F, 0.94F,
                      this.table1.getSurfaceOffsetNoTable() / 96.0F);
    this.addWorldItem("Base.KitchenKnife", this.table1.getSquare(), 0.492F,
                      0.29F, this.table1.getSurfaceOffsetNoTable() / 96.0F, 1);
    string = "farming.Tomato";
    int0 = Rand.Next(0, 4);
    switch (int0) {
    case 0:
      string = "Base.BellPepper";
      break;
    case 1:
      string = "Base.Broccoli";
      break;
    case 2:
      string = "Base.Carrots";
    }

    this.addWorldItem(string, this.table1.getSquare(), 0.77F, 0.97F,
                      this.table1.getSurfaceOffsetNoTable() / 96.0F, 70);
  }
}
} // namespace TableStories
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
