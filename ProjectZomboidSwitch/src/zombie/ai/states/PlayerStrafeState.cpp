#include "zombie/ai/states/PlayerStrafeState.h"

namespace zombie {
namespace ai {
namespace states {

PlayerStrafeState& PlayerStrafeState::instance() {
    static PlayerStrafeState _instance;
    return _instance;
}
}

void PlayerStrafeState::enter(IsoGameCharacter* var1) {
    if (var1->getPreviousActionContextStateName() != "aim") {
        InventoryItem* item = var1->getPrimaryHandItem();
        if (item && item->getBringToBearSound()) {
            var1->getEmitter()->playSoundImpl(item->getBringToBearSound(), nullptr);
        }
    }
    DebugLog::AI.debug("PlayerStrafeState::enter: sound played if needed");
}
}

void PlayerStrafeState::execute(IsoGameCharacter* var1) {
    // No-op, but add debug
    DebugLog::AI.debug("PlayerStrafeState::execute: called");
}
}

void PlayerStrafeState::exit(IsoGameCharacter* var1) {
    // No-op, but add debug
    DebugLog::AI.debug("PlayerStrafeState::exit: called");
}
}

void PlayerStrafeState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    // No-op, but add debug
    DebugLog::AI.debug("PlayerStrafeState::animEvent: called");
}
}

} // namespace states
} // namespace ai
} // namespace zombie
