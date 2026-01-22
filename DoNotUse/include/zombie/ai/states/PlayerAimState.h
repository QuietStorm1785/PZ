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
#include "zombie/inventory/InventoryItem.h"

namespace zombie {
namespace ai {
namespace states {


class PlayerAimState : public State {
public:
    static const PlayerAimState _instance = std::make_shared<PlayerAimState>();

    static PlayerAimState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      if (!"strafe" == var1.getPreviousActionContextStateName())) {
    InventoryItem var2 = var1.getPrimaryHandItem();
         if (var2 != nullptr && var2.getBringToBearSound() != nullptr) {
            var1.getEmitter().playSoundImpl(var2.getBringToBearSound(), nullptr);
         }
      }
   }

    void execute(IsoGameCharacter var1) {
   }

    void exit(IsoGameCharacter var1) {
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
