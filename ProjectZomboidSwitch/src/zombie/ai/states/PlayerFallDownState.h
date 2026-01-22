#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerFallDownState : public State {
public:
    static const PlayerFallDownState _instance = std::make_shared<PlayerFallDownState>();

    static PlayerFallDownState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      var1.clearVariable("bKnockedDown");
      if (var1.isDead() && !GameServer.bServer && !GameClient.bClient) {
         var1.Kill(nullptr);
      }
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
      var1.setOnFloor(true);
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (GameClient.bClient && var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
