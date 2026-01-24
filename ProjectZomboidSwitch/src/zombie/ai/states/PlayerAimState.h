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
   static PlayerAimState& instance() {
      static PlayerAimState _instance;
      return _instance;
   }


   void enter(IsoGameCharacter* var1) override {
      if (var1 && var1->getPreviousActionContextStateName() != "strafe") {
         InventoryItem* var2 = var1->getPrimaryHandItem();
         if (var2 && var2->getBringToBearSound()) {
            var1->getEmitter()->playSoundImpl(var2->getBringToBearSound(), nullptr);
         }
      }
   }

   void execute(IsoGameCharacter* var1) override {}

   void exit(IsoGameCharacter* var1) override {}

   void animEvent(IsoGameCharacter* var1, AnimEvent* var2) override {}
}
} // namespace states
} // namespace ai
} // namespace zombie
