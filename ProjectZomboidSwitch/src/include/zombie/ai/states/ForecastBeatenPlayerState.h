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

namespace zombie {
namespace ai {
namespace states {


class ForecastBeatenPlayerState : public State {
public:
    static const ForecastBeatenPlayerState _instance = std::make_shared<ForecastBeatenPlayerState>();

    static ForecastBeatenPlayerState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      var1.setReanimateTimer(30.0F);
   }

    void execute(IsoGameCharacter var1) {
      if (var1.getCurrentSquare() != nullptr) {
         var1.setReanimateTimer(var1.getReanimateTimer() - GameTime.getInstance().getMultiplier() / 1.6F);
         if (var1.getReanimateTimer() <= 0.0F) {
            var1.setReanimateTimer(0.0F);
            var1.setVariable("bKnockedDown", true);
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
