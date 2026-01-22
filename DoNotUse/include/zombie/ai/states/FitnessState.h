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
#include "zombie/network/GameClient.h"

namespace zombie {
namespace ai {
namespace states {


class FitnessState : public State {
public:
    static const FitnessState _instance = std::make_shared<FitnessState>();

    static FitnessState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      var1.setVariable("FitnessFinished", false);
      var1.clearVariable("ExerciseStarted");
      var1.clearVariable("ExerciseEnded");
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      if (GameClient.bClient && dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
         GameClient.sendEvent((IsoPlayer)var1, "EventUpdateFitness");
      }

      var1.setIgnoreMovement(false);
      var1.clearVariable("FitnessFinished");
      var1.clearVariable("ExerciseStarted");
      var1.clearVariable("ExerciseHand");
      var1.clearVariable("FitnessStruggle");
      var1.setVariable("ExerciseEnded", true);
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
