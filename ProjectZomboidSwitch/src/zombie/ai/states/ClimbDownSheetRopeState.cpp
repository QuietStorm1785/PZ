#include "zombie/ai/states/ClimbDownSheetRopeState.h"

namespace zombie {
namespace ai {
namespace states {

ClimbDownSheetRopeState& ClimbDownSheetRopeState::instance() {
    static ClimbDownSheetRopeState _instance;
    return _instance;
}

void ClimbDownSheetRopeState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClimbingDownSheetRope", true);
    DebugLog::AI.debug("ClimbDownSheetRopeState::enter: IsClimbingDownSheetRope set true for %p", var1);
}

void ClimbDownSheetRopeState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    // Example: reduce endurance while climbing down
    var1->getStats()->endurance -= 0.05f;
    DebugLog::AI.debug("ClimbDownSheetRopeState::execute: endurance reduced for %p", var1);
}

void ClimbDownSheetRopeState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsClimbingDownSheetRope", false);
    DebugLog::AI.debug("ClimbDownSheetRopeState::exit: IsClimbingDownSheetRope set false for %p", var1);
}

float ClimbDownSheetRopeState::getClimbDownSheetRopeSpeed(IsoGameCharacter* var1) {
    if (!var1) return 0.0f;
    float baseSpeed = 1.0f;
    if (var1->getStats()->endurance < 0.2f) {
        baseSpeed *= 0.5f; // slower if tired
    }
    DebugLog::AI.debug("ClimbDownSheetRopeState::getClimbDownSheetRopeSpeed: speed=%.2f for %p", baseSpeed, var1);
    return baseSpeed;
}

} // namespace states
} // namespace ai
} // namespace zombie
