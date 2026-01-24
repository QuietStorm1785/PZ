#include "zombie/ai/states/WalkTowardState.h"

namespace zombie {
namespace ai {
namespace states {

WalkTowardState& WalkTowardState::instance() {
    static WalkTowardState _instance;
    return _instance;
}

void WalkTowardState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsWalkingToward", true);
    DebugLog::AI.debug("WalkTowardState::enter: IsWalkingToward set true for %p", var1);
}

void WalkTowardState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("WalkToward");
    DebugLog::AI.debug("WalkTowardState::execute: playing walk toward animation for %p", var1);
}

void WalkTowardState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsWalkingToward", false);
    DebugLog::AI.debug("WalkTowardState::exit: IsWalkingToward set false for %p", var1);
}

void WalkTowardState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "WalkTowardFinished") {
        var1->setVariable("IsWalkingToward", false);
        DebugLog::AI.debug("WalkTowardState::animEvent: WalkTowardFinished for %p", var1);
    }
}

bool WalkTowardState::isMoving(IsoGameCharacter* var1) {
    if (!var1) return false;
    bool moving = var1->getVariableBoolean("IsWalkingToward");
    DebugLog::AI.debug("WalkTowardState::isMoving: %p moving=%d", var1, moving);
    return moving;
}

bool WalkTowardState::isPathClear(IsoGameCharacter* var1, float var2, float var3, float var4) {
    if (!var1) return false;
    // Example: check if path is clear using game logic
    bool clear = var1->isPathClear(var2, var3, var4);
    DebugLog::AI.debug("WalkTowardState::isPathClear: path clear=%d for %p", clear, var1);
    return clear;
}

bool WalkTowardState::calculateTargetLocation(IsoZombie* var1, Vector2& var2) {
    if (!var1) return false;
    // Example: calculate target location for zombie
    var2 = var1->getTargetLocation();
    bool valid = (var2.x != 0.0f || var2.y != 0.0f);
    DebugLog::AI.debug("WalkTowardState::calculateTargetLocation: target=(%.2f, %.2f) valid=%d for %p", var2.x, var2.y, valid, var1);
    return valid;
}

} // namespace states
} // namespace ai
} // namespace zombie
