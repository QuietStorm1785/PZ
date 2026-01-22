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
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSGunmanInBathroom : public RandomizedDeadSurvivorBase {
public:
    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = super.getRoom(var1, "bathroom");
    IsoDeadBody var3 = RandomizedDeadSurvivorBase.createRandomDeadBody(var2, Rand.Next(5, 10));
      if (var3 != nullptr) {
         var3.setPrimaryHandItem(super.addRandomRangedWeapon(var3.getContainer(), true, false, false));
    int var4 = Rand.Next(1, 4);

         for (int var5 = 0; var5 < var4; var5++) {
            var3.getContainer().AddItem(super.addRandomRangedWeapon(var3.getContainer(), true, true, true));
         }
      }
   }

    public RDSGunmanInBathroom() {
      this.name = "Bathroom Gunman";
      this.setChance(5);
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
