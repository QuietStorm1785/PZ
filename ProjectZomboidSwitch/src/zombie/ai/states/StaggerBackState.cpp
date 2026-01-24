#include "zombie/ai/states/StaggerBackState.h"

namespace zombie {
namespace ai {
namespace states {

StaggerBackState& StaggerBackState::instance() {
    static StaggerBackState _instance;
    return _instance;
}

void StaggerBackState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsStaggeringBack", true);
    DebugLog::AI.debug("StaggerBackState::enter: IsStaggeringBack set true for %p", var1);
}

void StaggerBackState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("StaggerBack");
    DebugLog::AI.debug("StaggerBackState::execute: playing stagger back animation for %p", var1);
}

void StaggerBackState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsStaggeringBack", false);
    DebugLog::AI.debug("StaggerBackState::exit: IsStaggeringBack set false for %p", var1);
}

float StaggerBackState::getMaxStaggerTime(IsoGameCharacter* var1) {
    if (!var1) return 0.0f;
    float baseTime = 1.5f;
    if (var1->getStats()->endurance < 0.3f) {
        baseTime *= 1.2f;
    }
    DebugLog::AI.debug("StaggerBackState::getMaxStaggerTime: time=%.2f for %p", baseTime, var1);
    return baseTime;
}

void StaggerBackState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "StaggerBackFinished") {
        var1->setVariable("IsStaggeringBack", false);
        DebugLog::AI.debug("StaggerBackState::animEvent: StaggerBackFinished for %p", var1);
    }
}

} // namespace states
} // namespace ai
} // namespace zombie
