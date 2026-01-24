#include "zombie/ai/states/ClimbSheetRopeState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbSheetRopeState& ClimbSheetRopeState::instance() {
    static ClimbSheetRopeState _instance;
    return _instance;
}

void ClimbSheetRopeState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClimbingSheetRope", true);
    DebugLog::AI.debug("ClimbSheetRopeState::enter: IsClimbingSheetRope set true for %p", var1);
}

void ClimbSheetRopeState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->getStats()->endurance -= 0.04f;
    DebugLog::AI.debug("ClimbSheetRopeState::execute: endurance reduced for %p", var1);
}

void ClimbSheetRopeState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClimbingSheetRope", false);
    DebugLog::AI.debug("ClimbSheetRopeState::exit: IsClimbingSheetRope set false for %p", var1);
}

float ClimbSheetRopeState::getClimbSheetRopeSpeed(IsoGameCharacter* var1) {
    if (!var1) return 0.0f;
    float baseSpeed = 1.0f;
    if (var1->getStats()->endurance < 0.2f) {
        baseSpeed *= 0.6f;
    }
    DebugLog::AI.debug("ClimbSheetRopeState::getClimbSheetRopeSpeed: speed=%.2f for %p", baseSpeed, var1);
    return baseSpeed;
}

} // namespace states
} // namespace ai
} // namespace zombie
