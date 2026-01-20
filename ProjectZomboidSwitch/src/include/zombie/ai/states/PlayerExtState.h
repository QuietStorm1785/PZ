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


class PlayerExtState : public State {
public:
    static const PlayerExtState _instance = std::make_shared<PlayerExtState>();

    static PlayerExtState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setVariable("ExtPlaying", true);
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      var1.clearVariable("ExtPlaying");
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if ("ExtFinishing".equalsIgnoreCase(var2.m_EventName)) {
         var1.setVariable("ExtPlaying", false);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
