#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {


class FakeDeadZombieState : public State {
public:
    static const FakeDeadZombieState _instance = std::make_shared<FakeDeadZombieState>();

    static FakeDeadZombieState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setVisibleToNPCs(false);
      var1.setCollidable(false);
      ((IsoZombie)var1).setFakeDead(true);
      var1.setOnFloor(true);
   }

    void execute(IsoGameCharacter var1) {
      if (var1.isDead()) {
         if (GameClient.bClient && dynamic_cast<IsoZombie*>(var1) != nullptr) {
            GameClient.sendZombieDeath((IsoZombie)var1);
         }

         if (!GameClient.bClient) {
    std::make_shared<IsoDeadBody>();
         }
      } else if (Core.bLastStand) {
         ((IsoZombie)var1).setFakeDead(false);
      }
   }

    void exit(IsoGameCharacter var1) {
      ((IsoZombie)var1).setFakeDead(false);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
