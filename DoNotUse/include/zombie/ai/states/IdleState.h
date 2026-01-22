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
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace ai {
namespace states {


class IdleState : public State {
public:
    static const IdleState _instance = std::make_shared<IdleState>();

    static IdleState instance() {
    return _instance;
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("PlaySound") && !StringUtils.isNullOrEmpty(var2.m_ParameterValue)) {
         var1.getSquare().playSound(var2.m_ParameterValue);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
