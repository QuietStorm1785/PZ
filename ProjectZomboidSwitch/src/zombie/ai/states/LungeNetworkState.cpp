#include "zombie/ai/states/LungeNetworkState.h"

namespace zombie {
namespace ai {
namespace states {

LungeNetworkState& LungeNetworkState::instance() {
    static LungeNetworkState _instance;
    return _instance;
}

void LungeNetworkState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsLunging", true);
    DebugLog::AI.debug("LungeNetworkState::enter: IsLunging set true for %p", var1);
}

void LungeNetworkState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    // Example: reduce stamina during lunge
    var1->getStats()->endurance -= 0.1f;
    DebugLog::AI.debug("LungeNetworkState::execute: endurance reduced for %p", var1);
}

void LungeNetworkState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsLunging", false);
    DebugLog::AI.debug("LungeNetworkState::exit: IsLunging set false for %p", var1);
}

bool LungeNetworkState::isMoving(IsoGameCharacter* var1) {
    if (!var1) return false;
    bool moving = var1->getVariableBoolean("IsLunging");
    DebugLog::AI.debug("LungeNetworkState::isMoving: %p moving=%d", var1, moving);
    return moving;
}

} // namespace states
} // namespace ai
} // namespace zombie
