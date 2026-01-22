#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSCorpsePsycho : public RandomizedDeadSurvivorBase {
public:
    public RDSCorpsePsycho() {
      this.name = "Corpse Psycho";
      this.setChance(1);
      this.setMinimumDays(120);
      this.setUnique(true);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getRoom(var1, "kitchen");
    int var3 = Rand.Next(3, 7);

      for (int var4 = 0; var4 < var3; var4++) {
    IsoDeadBody var5 = RandomizedDeadSurvivorBase.createRandomDeadBody(var2, Rand.Next(5, 10));
         if (var5 != nullptr) {
            super.addBloodSplat(var5.getCurrentSquare(), Rand.Next(7, 12));
         }
      }

    std::vector var6 = super.addZombies(var1, 1, "Doctor", nullptr, var2);
      if (!var6.empty()) {
         for (int var7 = 0; var7 < 8; var7++) {
            ((IsoZombie)var6.get(0)).addBlood(nullptr, false, true, false);
         }

         var1.bAlarmed = false;
      }
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
