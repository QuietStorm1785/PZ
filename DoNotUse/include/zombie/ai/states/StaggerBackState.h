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
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"

namespace zombie {
namespace ai {
namespace states {


class StaggerBackState : public State {
public:
    static const StaggerBackState _instance = std::make_shared<StaggerBackState>();

    static StaggerBackState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setStateEventDelayTimer(this.getMaxStaggerTime(var1));
   }

    void execute(IsoGameCharacter var1) {
      if (var1.hasAnimationPlayer()) {
         var1.getAnimationPlayer().setTargetToAngle();
      }

      var1.getVectorFromDirection(var1.getForwardDirection());
   }

    void exit(IsoGameCharacter var1) {
      if (var1.isZombie()) {
         ((IsoZombie)var1).setStaggerBack(false);
      }

      var1.setShootable(true);
   }

    float getMaxStaggerTime(IsoGameCharacter var1) {
    float var2 = 35.0F * var1.getHitForce() * var1.getStaggerTimeMod();
      if (var2 < 20.0F) {
         return 20.0F;
      } else {
         return var2 > 30.0F ? 30.0F : var2;
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("SetState")) {
    IsoZombie var3 = (IsoZombie)var1;
         var3.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Pushed);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
