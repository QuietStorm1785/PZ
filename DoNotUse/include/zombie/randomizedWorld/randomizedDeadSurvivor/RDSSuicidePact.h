#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {


class RDSSuicidePact : public RandomizedDeadSurvivorBase {
public:
    public RDSSuicidePact() {
      this.name = "Suicide Pact";
      this.setChance(7);
      this.setMinimumDays(60);
   }

    void randomizeDeadSurvivor(BuildingDef var1) {
    RoomDef var2 = this.getLivingRoomOrKitchen(var1);
    IsoGameCharacter var3 = RandomizedDeadSurvivorBase.createRandomZombieForCorpse(var2);
      if (var3 != nullptr) {
         var3.addVisualDamage("ZedDmg_HEAD_Bullet");
    IsoDeadBody var4 = RandomizedDeadSurvivorBase.createBodyFromZombie(var3);
         if (var4 != nullptr) {
            this.addBloodSplat(var4.getSquare(), 4);
            var4.setPrimaryHandItem(this.addWeapon("Base.Pistol", true));
            var3 = RandomizedDeadSurvivorBase.createRandomZombieForCorpse(var2);
            if (var3 != nullptr) {
               var3.addVisualDamage("ZedDmg_HEAD_Bullet");
               var4 = RandomizedDeadSurvivorBase.createBodyFromZombie(var3);
               if (var4 != nullptr) {
                  this.addBloodSplat(var4.getSquare(), 4);
               }
            }
         }
      }
   }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
