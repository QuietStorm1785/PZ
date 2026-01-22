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
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerKnockedDown : public State {
public:
    static const PlayerKnockedDown _instance = std::make_shared<PlayerKnockedDown>();

    static PlayerKnockedDown instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      ((IsoPlayer)var1).setBlockMovement(true);
      var1.setHitReaction("");
   }

    void execute(IsoGameCharacter var1) {
      if (var1.isDead()) {
         if (!GameServer.bServer && !GameClient.bClient) {
            var1.Kill(nullptr);
         }
      } else {
         var1.setReanimateTimer(var1.getReanimateTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("FallOnBack")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("setSitOnGround")) {
         var1.setSitOnGround(bool.parseBoolean(var2.m_ParameterValue));
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
      ((IsoPlayer)var1).setBlockMovement(false);
      ((IsoPlayer)var1).setKnockedDown(false);
      var1.setOnFloor(true);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
