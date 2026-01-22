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
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {


class FishingState : public State {
public:
    static const FishingState _instance = std::make_shared<FishingState>();
    float pauseTime = 0.0F;
    std::string stage = nullptr;

    static FishingState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      DebugLog.log("FISHINGSTATE - ENTER");
      var1.setVariable("FishingFinished", false);
      this.pauseTime = Rand.Next(60.0F, 120.0F);
   }

    void execute(IsoGameCharacter var1) {
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
    std::string var2 = var1.getVariableString("FishingStage");
         if (var2 != nullptr && !var2 == this.stage)) {
            this.stage = var2;
            if (!var2 == "idle")) {
               GameClient.sendEvent((IsoPlayer)var1, "EventFishing");
            }
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      DebugLog.log("FISHINGSTATE - EXIT");
      var1.clearVariable("FishingStage");
      var1.clearVariable("FishingFinished");
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
