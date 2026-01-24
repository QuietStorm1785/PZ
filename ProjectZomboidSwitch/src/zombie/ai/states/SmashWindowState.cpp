#include "zombie/ai/states/SmashWindowState.h"

namespace zombie {
namespace ai {
namespace states {

SmashWindowState& SmashWindowState::instance() {
    static SmashWindowState _instance;
    return _instance;
}

void SmashWindowState::enter(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsSmashingWindow", true);
    DebugLog::AI.debug("SmashWindowState::enter: IsSmashingWindow set true for %p", var1);
}

void SmashWindowState::execute(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->playAnimation("SmashWindow");
    DebugLog::AI.debug("SmashWindowState::execute: playing smash window animation for %p", var1);
}

void SmashWindowState::exit(IsoGameCharacter* var1) {
    if (!var1) return;
    var1->setVariable("IsSmashingWindow", false);
    DebugLog::AI.debug("SmashWindowState::exit: IsSmashingWindow set false for %p", var1);
}

void SmashWindowState::animEvent(IsoGameCharacter* var1, AnimEvent* var2) {
    if (!var1 || !var2) return;
    if (var2->m_EventName == "WindowSmashed") {
        var1->setVariable("IsSmashingWindow", false);
        DebugLog::AI.debug("SmashWindowState::animEvent: WindowSmashed for %p", var1);
    }
}

bool SmashWindowState::isDoingActionThatCanBeCancelled() {
    // Example: smashing window can be cancelled
    DebugLog::AI.debug("SmashWindowState::isDoingActionThatCanBeCancelled: true");
    return true;
}

} // namespace states
} // namespace ai
} // namespace zombie
