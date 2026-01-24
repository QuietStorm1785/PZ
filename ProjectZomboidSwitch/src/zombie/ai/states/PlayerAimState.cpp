#include "zombie/ai/states/PlayerAimState.h"

namespace zombie {
namespace ai {
namespace states {


void PlayerAimState::enter(IsoGameCharacter* var1) {
    if (var1 && var1->getPreviousActionContextStateName() != "strafe") {
        InventoryItem* var2 = var1->getPrimaryHandItem();
        if (var2 && var2->getBringToBearSound()) {
            var1->getEmitter()->playSoundImpl(var2->getBringToBearSound(), nullptr);
        }
    }
}

void PlayerAimState::execute(IsoGameCharacter* var1) {}

void PlayerAimState::exit(IsoGameCharacter* var1) {}

void PlayerAimState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {}

} // namespace states
} // namespace ai
} // namespace zombie
