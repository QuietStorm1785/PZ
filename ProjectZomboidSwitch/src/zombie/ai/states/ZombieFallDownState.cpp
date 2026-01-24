#include "zombie/ai/states/ZombieFallDownState.h"

namespace zombie {
namespace ai {
namespace states {

ZombieFallDownState& ZombieFallDownState::instance() {
    static ZombieFallDownState _instance;
    return _instance;
}

void ZombieFallDownState::enter(IsoGameCharacter* var1) {
    // Example: Set up fall down variables
    var1->setVariable("FallDownStarted", true);
    DebugLog::AI.debug("ZombieFallDownState::enter called");
}

void ZombieFallDownState::execute(IsoGameCharacter* var1) {
    // Example: Perform fall down logic
    if (var1->getVariableBoolean("FallDownStarted")) {
        var1->doFallDown();
        DebugLog::AI.debug("ZombieFallDownState::execute called");
    }
}

void ZombieFallDownState::exit(IsoGameCharacter* var1) {
    // Example: Clean up fall down variables
    var1->clearVariable("FallDownStarted");
    DebugLog::AI.debug("ZombieFallDownState::exit called");
}

void ZombieFallDownState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    // Example: Handle animation events for falling down
    if (StringUtils::equalsIgnoreCase(var2->m_EventName, "FallenOnKnees")) {
        var1->fallenOnKnees();
        DebugLog::AI.debug("ZombieFallDownState::animEvent: FallenOnKnees");
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
