#pragma once
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class FishingState : public State {
public:
  static const FishingState _instance = new FishingState();
  float pauseTime = 0.0F;
  std::string stage = null;

  static FishingState instance() { return _instance; }

  void enter(IsoGameCharacter owner) {
    DebugLog.log("FISHINGSTATE - ENTER");
    owner.setVariable("FishingFinished", false);
    this.pauseTime = Rand.Next(60.0F, 120.0F);
  }

  void execute(IsoGameCharacter owner) {
    if (GameClient.bClient && owner instanceof
        IsoPlayer && ((IsoPlayer)owner).isLocalPlayer()) {
      std::string string = owner.getVariableString("FishingStage");
      if (string != nullptr && !string == this.stage)) {
          this.stage = string;
          if (!string == "idle")) {
                    GameClient.sendEvent((IsoPlayer)owner, "EventFishing");
                }
        }
    }
  }

  void exit(IsoGameCharacter owner) {
    DebugLog.log("FISHINGSTATE - EXIT");
    owner.clearVariable("FishingStage");
    owner.clearVariable("FishingFinished");
  }

  void animEvent(IsoGameCharacter owner, AnimEvent event) {}
}
} // namespace states
} // namespace ai
} // namespace zombie
