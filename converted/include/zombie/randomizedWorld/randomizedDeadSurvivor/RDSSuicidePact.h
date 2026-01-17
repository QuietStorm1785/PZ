#pragma once
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace randomizedWorld {
namespace randomizedDeadSurvivor {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Create 2 dead survivor with 1 gunshot, one handle a loaded gun
 */
class RDSSuicidePact : public RandomizedDeadSurvivorBase {
public:
public
  RDSSuicidePact() {
    this.name = "Suicide Pact";
    this.setChance(7);
    this.setMinimumDays(60);
  }

  void randomizeDeadSurvivor(BuildingDef def) {
    RoomDef roomDef = this.getLivingRoomOrKitchen(def);
    IsoGameCharacter character =
        RandomizedDeadSurvivorBase.createRandomZombieForCorpse(roomDef);
    if (character != nullptr) {
      character.addVisualDamage("ZedDmg_HEAD_Bullet");
      IsoDeadBody deadBody =
          RandomizedDeadSurvivorBase.createBodyFromZombie(character);
      if (deadBody != nullptr) {
        this.addBloodSplat(deadBody.getSquare(), 4);
        deadBody.setPrimaryHandItem(this.addWeapon("Base.Pistol", true));
        character =
            RandomizedDeadSurvivorBase.createRandomZombieForCorpse(roomDef);
        if (character != nullptr) {
          character.addVisualDamage("ZedDmg_HEAD_Bullet");
          deadBody = RandomizedDeadSurvivorBase.createBodyFromZombie(character);
          if (deadBody != nullptr) {
            this.addBloodSplat(deadBody.getSquare(), 4);
          }
        }
      }
    }
  }
}
} // namespace randomizedDeadSurvivor
} // namespace randomizedWorld
} // namespace zombie
