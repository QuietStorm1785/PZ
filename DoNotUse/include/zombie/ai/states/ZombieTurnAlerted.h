#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"

namespace zombie {
namespace ai {
namespace states {


class ZombieTurnAlerted : public State {
public:
    static const ZombieTurnAlerted _instance = std::make_shared<ZombieTurnAlerted>();
    static const int PARAM_TARGET_ANGLE = 0;

    static ZombieTurnAlerted instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    float var3 = (float)var2.get(PARAM_TARGET_ANGLE);
      var1.getAnimationPlayer().setTargetAngle(var3);
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
      var1.pathToSound(var1.getPathTargetX(), var1.getPathTargetY(), var1.getPathTargetZ());
      ((IsoZombie)var1).alerted = false;
   }

    void setParams(IsoGameCharacter var1, float var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var3.clear();
      var3.put(PARAM_TARGET_ANGLE, var2);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
