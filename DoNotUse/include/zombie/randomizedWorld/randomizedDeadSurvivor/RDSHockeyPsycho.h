#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSHockeyPsycho : public RandomizedDeadSurvivorBase {
public:
    public RDSHockeyPsycho() {
      this.name = "Hockey Psycho (friday 13th!)";
      this.setUnique(true);
      this.setChance(1);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
    std::vector var3 = this.addZombies(var1, 1, "HockeyPsycho", 0, var2);
      if (var3 != nullptr && !var3.empty()) {
    IsoZombie var4 = (IsoZombie)var3.get(0);
         var4.addBlood(BloodBodyPartType.Head, true, true, true);

         for (int var5 = 0; var5 < 10; var5++) {
            var4.addBlood(nullptr, true, false, true);
            var4.addDirt(nullptr, Rand.Next(0, 3), true);
         }
      }

      for (int var6 = 0; var6 < 10; var6++) {
    IsoDeadBody var7 = createRandomDeadBody(this.getRandomRoom(var1, 2), Rand.Next(5, 20));
         if (var7 != nullptr) {
            this.addTraitOfBlood(IsoDirections.getRandom(), 15, (int)var7.x, (int)var7.y, (int)var7.z);
            this.addTraitOfBlood(IsoDirections.getRandom(), 15, (int)var7.x, (int)var7.y, (int)var7.z);
            this.addTraitOfBlood(IsoDirections.getRandom(), 15, (int)var7.x, (int)var7.y, (int)var7.z);
         }
      }

      var1.bAlarmed = false;
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
