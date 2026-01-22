#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerEmoteState : public State {
public:
    static const PlayerEmoteState _instance = std::make_shared<PlayerEmoteState>();

    static PlayerEmoteState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setVariable("EmotePlaying", true);
      var1.resetModelNextFrame();
   }

    void execute(IsoGameCharacter var1) {
    IsoPlayer var2 = (IsoPlayer)var1;
      if (var2.pressedCancelAction()) {
         var1.setVariable("EmotePlaying", false);
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.clearVariable("EmotePlaying");
      var1.resetModelNextFrame();
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if ("EmoteFinishing".equalsIgnoreCase(var2.m_EventName)) {
         var1.setVariable("EmotePlaying", false);
      }

      if ("EmoteLooped".equalsIgnoreCase(var2.m_EventName)) {
      }
   }

    bool isDoingActionThatCanBeCancelled() {
    return true;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
