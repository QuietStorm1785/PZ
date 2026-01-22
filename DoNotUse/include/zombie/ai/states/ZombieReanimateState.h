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


class ZombieReanimateState : public State {
public:
    static const ZombieReanimateState _instance = std::make_shared<ZombieReanimateState>();

    static ZombieReanimateState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var2.clearVariable("ReanimateAnim");
      var2.parameterZombieState.setState(zombie.audio.parameters.ParameterZombieState.State.Idle);
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
    IsoZombie var2 = (IsoZombie)var1;
      var2.clearVariable("ReanimateAnim");
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    IsoZombie var3 = (IsoZombie)var1;
      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("ReanimateAnimFinishing")) {
         var3.setReanimate(false);
         var3.setFallOnFront(true);
      }

      if (var2.m_EventName.equalsIgnoreCase("FallOnFront")) {
         var1.setFallOnFront(bool.parseBoolean(var2.m_ParameterValue));
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
