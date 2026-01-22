#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSGunslinger : public RandomizedDeadSurvivorBase {
public:
    void randomizeDeadSurvivor(BuildingDef var1) {
    IsoGridSquare var2 = var1.getFreeSquareInRoom();
      if (var2 != nullptr) {
    IsoDeadBody var3 = RandomizedDeadSurvivorBase.createRandomDeadBody(var2.getX(), var2.getY(), var2.getZ(), nullptr, 0);
         if (var3 != nullptr) {
            var3.setPrimaryHandItem(super.addRandomRangedWeapon(var3.getContainer(), true, false, false));
    int var4 = Rand.Next(1, 4);

            for (int var5 = 0; var5 < var4; var5++) {
               var3.getContainer().AddItem(super.addRandomRangedWeapon(var3.getContainer(), true, true, true));
            }
         }
      }
   }

    public RDSGunslinger() {
      this.name = "Gunslinger";
      this.setChance(5);
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
