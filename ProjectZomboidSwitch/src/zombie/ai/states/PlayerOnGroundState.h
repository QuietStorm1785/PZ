#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerOnGroundState : public State {
public:
    static const PlayerOnGroundState _instance = std::make_shared<PlayerOnGroundState>();

    static PlayerOnGroundState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      ((IsoPlayer)var1).setBlockMovement(true);
      var1.setVariable("bAnimEnd", false);
   }

    void execute(IsoGameCharacter var1) {
      if (!GameServer.bServer && var1.isDead()) {
         var1.die();
      } else {
         var1.setReanimateTimer(var1.getReanimateTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
      ((IsoPlayer)var1).setBlockMovement(false);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
