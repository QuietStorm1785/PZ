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


class ZombieFallingState : public State {
public:
    static const ZombieFallingState _instance = std::make_shared<ZombieFallingState>();

    static ZombieFallingState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setVariable("bHardFall", false);
      var1.clearVariable("bLandAnimFinished");
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      var1.clearVariable("bHardFall");
      var1.clearVariable("bLandAnimFinished");
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
