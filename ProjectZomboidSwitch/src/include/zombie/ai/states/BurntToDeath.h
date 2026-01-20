#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/IsoZombie/ZombieSound.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TutorialManager.h"

namespace zombie {
namespace ai {
namespace states {


class BurntToDeath : public State {
public:
    static const BurntToDeath _instance = std::make_shared<BurntToDeath>();

    static BurntToDeath instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      if (dynamic_cast<IsoSurvivor*>(var1) != nullptr) {
         var1.getDescriptor().bDead = true;
      }

      if (!(dynamic_cast<IsoZombie*>(var1) != nullptr)) {
         var1.PlayAnimUnlooped("Die");
      } else {
         var1.PlayAnimUnlooped("ZombieDeath");
      }

      var1.def.AnimFrameIncrease = 0.25F;
      var1.setStateMachineLocked(true);
    std::string var2 = var1.isFemale() ? "FemaleZombieDeath" : "MaleZombieDeath";
      var1.getEmitter().playVocals(var2);
      if (GameServer.bServer && dynamic_cast<IsoZombie*>(var1) != nullptr) {
         GameServer.sendZombieSound(ZombieSound.Burned, (IsoZombie)var1);
      }
   }

    void execute(IsoGameCharacter var1) {
      if ((int)var1.def.Frame == var1.sprite.CurrentAnim.Frames.size() - 1) {
         if (var1 == TutorialManager.instance.wife) {
            var1.dir = IsoDirections.S;
         }

         var1.RemoveAttachedAnims();
         if (GameClient.bClient && dynamic_cast<IsoZombie*>(var1) != nullptr) {
            GameClient.sendZombieDeath((IsoZombie)var1);
         }

         if (!GameClient.bClient) {
    std::make_shared<IsoDeadBody>();
         }
      }
   }

    void exit(IsoGameCharacter var1) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
