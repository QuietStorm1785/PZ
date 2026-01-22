#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerFallingState : public State {
public:
    static const PlayerFallingState _instance = std::make_shared<PlayerFallingState>();

    static PlayerFallingState instance() {
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
}
} // namespace states
} // namespace ai
} // namespace zombie
