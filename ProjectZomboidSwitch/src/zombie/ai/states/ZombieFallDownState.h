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

namespace zombie {
namespace ai {
namespace states {


class ZombieFallDownState : public State {
public:
    static const ZombieFallDownState _instance = std::make_shared<ZombieFallDownState>();

    static ZombieFallDownState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.blockTurning = true;
      var1.setHitReaction("");
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      var1.blockTurning = false;
      var1.setOnFloor(true);
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("PlayDeathSound")) {
         var1.setDoDeathSound(false);
         var1.playDeadSound();
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
