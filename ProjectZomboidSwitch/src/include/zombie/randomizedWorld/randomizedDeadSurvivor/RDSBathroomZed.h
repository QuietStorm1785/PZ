#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSBathroomZed : public RandomizedDeadSurvivorBase {
public:
   private const std::vector<std::string> items = std::make_unique<std::vector<>>();

    public RDSBathroomZed() {
      this.name = "Bathroom Zed";
      this.setChance(12);
      this.items.push_back("Base.BathTowel");
      this.items.push_back("Base.Razor");
      this.items.push_back("Base.Lipstick");
      this.items.push_back("Base.Comb");
      this.items.push_back("Base.Hairspray");
      this.items.push_back("Base.Toothbrush");
      this.items.push_back("Base.Cologne");
      this.items.push_back("Base.Perfume");
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getRoom(var1, "bathroom");
    int var3 = 1;
      if (var2.area > 6) {
         var3 = Rand.Next(1, 3);
      }

      this.addZombies(var1, var3, Rand.Next(2) == 0 ? "Bathrobe" : "Naked", nullptr, var2);
      this.addRandomItemsOnGround(var2, this.items, Rand.Next(2, 5));
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
