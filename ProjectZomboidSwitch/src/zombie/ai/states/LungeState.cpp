#include "zombie/ai/states/LungeState.h"

namespace zombie {
namespace ai {
namespace states {

LungeState& LungeState::instance() {
    static LungeState _instance;
    return _instance;
}

void LungeState::enter(IsoGameCharacter* var1) {
    // Example: Set up lunge variables
    var1->setVariable("LungeStarted", true);
    DebugLog::AI.debug("LungeState::enter called");
}

void LungeState::execute(IsoGameCharacter* var1) {
    // Example: Perform lunge movement
    if (var1->getVariableBoolean("LungeStarted")) {
        var1->moveLunge();
        DebugLog::AI.debug("LungeState::execute called");
    }
}

void LungeState::exit(IsoGameCharacter* var1) {
    // Example: Clean up lunge variables
    var1->clearVariable("LungeStarted");
    DebugLog::AI.debug("LungeState::exit called");
}

bool LungeState::isMoving(IsoGameCharacter* var1) {
    // Example: Check if character is moving during lunge
    bool moving = var1->getVariableBoolean("LungeStarted") && var1->isMoving();
    DebugLog::AI.debug("LungeState::isMoving: %s", moving ? "true" : "false");
    return moving;
}

} // namespace states
} // namespace ai
} // namespace zombie
